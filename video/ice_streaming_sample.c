// 2 modes to start: 0 - controlling (sender), 1 - controlled (receiver):
// ./ice_streaming_sample.o 0 $(host -4 -t A stun.stunprotocol.org | awk '{ print $4 }') --gst-debug-level=4
// ./ice_streaming_sample.o 1 $(host -4 -t A stun.stunprotocol.org | awk '{ print $4 }') --gst-debug-level=4
#include <gst/gst.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <agent.h>
  
typedef struct _CustomData {
  gboolean is_live;
  GstElement *pipeline;
} CustomData;

GMainLoop *gloop;

static gchar *stun_addr = NULL;
static guint stun_port;
static guint self_component_id;
static gboolean controlling;
static gboolean exit_thread, candidate_gathering_done, negotiation_done;
static GMutex gather_mutex, negotiate_mutex;
static GCond gather_cond, negotiate_cond;

static const gchar *state_name[] = {"disconnected", "gathering", "connecting",
                                    "connected", "ready", "failed"};

/* declarations */
static void cb_candidate_gathering_done(
  NiceAgent *agent, guint stream_id, gpointer data);

static void cb_component_state_changed(
  NiceAgent *agent, guint stream_id, guint component_id, guint state, gpointer data);

static void * example_thread(void *data);

static void cb_message (GstBus *bus, GstMessage *msg, CustomData *data);

/* main */
int main(int argc, char *argv[]) {
  GstMessage *msg;

  GThread *gexamplethread;

  // Parse arguments
  if (argc > 4 || argc < 2 || argv[1][1] != '\0') {
    fprintf(stderr, "Usage: %s 0|1 stun_addr [stun_port]\n", argv[0]);
    return EXIT_FAILURE;
  }
  controlling = argv[1][0] - '0';
  if (controlling != 0 && controlling != 1) {
    fprintf(stderr, "Usage: %s 0|1 stun_addr [stun_port]\n", argv[0]);
    return EXIT_FAILURE;
  }

  if (argc > 2) {
    stun_addr = argv[2];
    if (argc > 3) {
      stun_port = atoi(argv[3]);
    }
    else {
      stun_port = 3478;
    }

    g_debug("Using stun server '[%s]:%u'\n", stun_addr, stun_port);
  }

  #if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
  #endif

   
  /* Initialize GStreamer */
  gst_init (&argc, &argv);  

  gloop = g_main_loop_new (NULL, FALSE);

  // Run the mainloop and the example thread
  exit_thread = FALSE;
  gexamplethread = g_thread_new("example thread", &example_thread, NULL);
  g_main_loop_run (gloop);
  exit_thread = TRUE;

  g_thread_join (gexamplethread);

   
  /* Free resources */
  g_main_loop_unref(gloop);

  return EXIT_SUCCESS;
}

/**
 * Performs ICE negotiation and starts gstreamer pipeline
 */
static void * example_thread(void *data) {
  NiceAgent *agent;
  GIOChannel* io_stdin;
  guint stream_id;
  gchar *line = NULL;
  gchar *sdp, *sdp64;

  GstStateChangeReturn ret;
  GstElement *pipeline, *source, *sink, *vertigotv;
  GstBus *bus;

  io_stdin = g_io_channel_unix_new(fileno(stdin));
  g_io_channel_set_flags (io_stdin, G_IO_FLAG_NONBLOCK, NULL);

  // Create the nice agent
  agent = nice_agent_new(
    g_main_loop_get_context (gloop),
    NICE_COMPATIBILITY_RFC5245);

  if (agent == NULL) {
    g_error("Failed to create agent");
  }

  // Set the STUN settings and controlling mode
  if (stun_addr) {
    g_object_set(G_OBJECT(agent), "stun-server", stun_addr, NULL);
    g_object_set(G_OBJECT(agent), "stun-server-port", stun_port, NULL);
  }
  g_object_set(G_OBJECT(agent), "controlling-mode", controlling, NULL);

  // Connect to the signals
  g_signal_connect(G_OBJECT(agent), "candidate-gathering-done",
      G_CALLBACK(cb_candidate_gathering_done), NULL);
  g_signal_connect(G_OBJECT(agent), "component-state-changed",
      G_CALLBACK(cb_component_state_changed), NULL);

  // Create a new stream with one component
  stream_id = nice_agent_add_stream(agent, 1);
  if (stream_id == 0) {
    g_error("Failed to add stream");
  }
  nice_agent_set_stream_name (agent, stream_id, "text");

  // Attach to the component to receive the data
  // Without this call, candidates cannot be gathered
  nice_agent_attach_recv(
    agent,
    stream_id,
    1,
    g_main_loop_get_context (gloop),
    6,
    NULL);

  // Start gathering local candidates
  if (!nice_agent_gather_candidates(agent, stream_id)) {
    g_error("Failed to start candidate gathering");
  }

  g_debug("waiting for candidate-gathering-done signal...");

  g_mutex_lock(&gather_mutex);
  while (!exit_thread && !candidate_gathering_done) {
    g_cond_wait(&gather_cond, &gather_mutex);
  }

  g_mutex_unlock(&gather_mutex);
  if (exit_thread) {
    goto end;
  }

  // Candidate gathering is done. Send our local candidates on stdout
  printf("Copy this line to remote client:\n");
  sdp = nice_agent_generate_local_sdp (agent);
  sdp64 = g_base64_encode ((const guchar *)sdp, strlen (sdp));
  printf("\n  %s\n", sdp64);
  g_free (sdp);
  g_free (sdp64);

  // Listen on stdin for the remote candidate list
  printf("Enter remote data (single line, no wrapping):\n");
  printf("> ");
  fflush (stdout);

  // TODO: we only need verificion key on receiver, on ????? who knows???
  while (!exit_thread) {
    GIOStatus s = g_io_channel_read_line (io_stdin, &line, NULL, NULL, NULL);
    if (s == G_IO_STATUS_NORMAL) {
      gsize sdp_len;

      sdp = (gchar *) g_base64_decode (line, &sdp_len);
      // Parse remote candidate list and set it on the agent
      if (sdp && nice_agent_parse_remote_sdp (agent, sdp) > 0) {
        g_free (sdp);
        g_free (line);
        break;
      } else {
        fprintf(stderr, "ERROR: failed to parse remote data\n");
        printf("Enter remote data (single line, no wrapping):\n");
        printf("> ");
        fflush (stdout);
      }
      g_free (sdp);
      g_free (line);
    } else if (s == G_IO_STATUS_AGAIN) {
      usleep (100000);
    }
  }

  g_debug("waiting for state READY or FAILED signal...");
  g_mutex_lock(&negotiate_mutex);
  while (!exit_thread && !negotiation_done) {
    g_cond_wait(&negotiate_cond, &negotiate_mutex);
  }

  g_mutex_unlock(&negotiate_mutex);
  if (exit_thread) {
    goto end;
  }

  // Now create pipelines depending on who is sending and who is receiving video stream
  printf("\nNegotiations complete:\n");
  fflush (stdout);

  /* ================== START PIPELINES CREATION CODE ================== */
  /* Create the empty pipeline */
  pipeline = gst_pipeline_new ("test-pipeline");

  GstElement *videoconvert, *h263p, *rtph263ppay;
    
  /* Create the elements */
  // sender
  if (controlling == 0) {
    source = gst_element_factory_make ("videotestsrc", "source");
    videoconvert = gst_element_factory_make ("videoconvert", "convert");
    h263p = gst_element_factory_make ("avenc_h263p", "h263p");
    rtph263ppay = gst_element_factory_make ("rtph263ppay", "rtph263ppay");
    sink = gst_element_factory_make ("nicesink", "sink");

    /* Modify the source's properties */
    g_object_set (source, "pattern", 0, NULL);

    g_object_set (sink, "agent", agent, NULL);
    g_object_set (sink, "stream", stream_id, NULL);
    g_object_set (sink, "component", self_component_id, NULL);

    if (!pipeline || !source || !videoconvert || !h263p || !rtph263ppay || !sink) {
      g_printerr ("Not all elements could be created.\n");
      return -1;
    }

    /* Build the pipeline */
    gst_bin_add_many (GST_BIN (pipeline), source, videoconvert, h263p, rtph263ppay, sink, NULL);
    if (
      gst_element_link (source, videoconvert) != TRUE ||
      gst_element_link (videoconvert, h263p) != TRUE ||
      gst_element_link (h263p, rtph263ppay) != TRUE ||
      gst_element_link (rtph263ppay, sink) != TRUE
    ) {
      g_printerr ("Elements could not be linked.\n");
      gst_object_unref (pipeline);
      return -1;
    }
  }

  // receiver
  else if (controlling == 1) {
    source = gst_element_factory_make ("nicesrc", "source");
    sink = gst_element_factory_make ("fakesink", "sink");

    g_object_set (source, "agent", agent, NULL);
    g_object_set (source, "stream", stream_id, NULL);
    g_object_set (source, "component", self_component_id, NULL);
    g_object_set (sink, "dump", 1, NULL);

    if (!pipeline || !source || !sink) {
      g_printerr ("Not all elements could be created.\n");
      return -1;
    }

    /* Build the pipeline */
    gst_bin_add_many (GST_BIN (pipeline), source, sink, NULL);
    if (gst_element_link (source, sink) != TRUE) {
      g_printerr ("Elements could not be linked.\n");
      gst_object_unref (pipeline);
      return -1;
    }
  }

  // error state
  else {
    g_printerr ("Neither sender nor receiver.\n");
    return -1;
  }

  /* Start playing */
  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    return -1;
  }
  
   
  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);


  CustomData customData;

  customData.pipeline = pipeline;
  customData.is_live = FALSE;

  gst_bus_add_signal_watch (bus);
  g_signal_connect (bus, "message", G_CALLBACK (cb_message), &customData);
  /* ================== END PIPELINES CREATION CODE ================== */

  while (TRUE) {
    usleep(10000);
  }

end:
  g_object_unref(agent);
  g_io_channel_unref (io_stdin);
  g_main_loop_quit (gloop);

  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);

  return NULL;
}

/*
 * Callback to be called when piepile receives message/data is updates
 */
static void cb_message (GstBus *bus, GstMessage *msg, CustomData *data) {   
  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_ERROR: {
      GError *err;
      gchar *debug;
       
      gst_message_parse_error (msg, &err, &debug);
      g_print ("Error: %s\n", err->message);
      g_error_free (err);
      g_free (debug);
       
      gst_element_set_state (data->pipeline, GST_STATE_READY);
      g_main_loop_quit (gloop);
      break;
    }
    case GST_MESSAGE_EOS:
      /* end-of-stream */
      gst_element_set_state (data->pipeline, GST_STATE_READY);
      g_main_loop_quit (gloop);
      break;
    case GST_MESSAGE_BUFFERING: {
      gint percent = 0;
       
      /* If the stream is live, we do not care about buffering. */
      if (data->is_live) break;
       
      gst_message_parse_buffering (msg, &percent);
      g_print ("Buffering (%3d%%)\r", percent);
      /* Wait until buffering is complete before start/resume playing */
      if (percent < 100)
        gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
      else
        gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
      break;
    }
    case GST_MESSAGE_CLOCK_LOST:
      /* Get a new clock */
      gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
      gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
      break;
    default:
      /* Unhandled message */
      break;
    }
}

/*
 * Callback to be called when candidate gathering was completed
 */
static void cb_candidate_gathering_done(
  NiceAgent *agent,
  guint stream_id,
  gpointer data) {

  g_debug("SIGNAL candidate gathering done\n");

  g_mutex_lock(&gather_mutex);
  candidate_gathering_done = TRUE;
  g_cond_signal(&gather_cond);
  g_mutex_unlock(&gather_mutex);
}

/*
 * Callback to be called when state is changed
 */
static void cb_component_state_changed(
  NiceAgent *agent,
  guint stream_id,
  guint component_id,
  guint state,
  gpointer data) {

  g_debug("SIGNAL: state changed %d %d %s[%d]\n",
      stream_id, component_id, state_name[state], state);

  if (state == NICE_COMPONENT_STATE_READY) {
    g_mutex_lock(&negotiate_mutex);
    negotiation_done = TRUE;
    g_cond_signal(&negotiate_cond);
    g_mutex_unlock(&negotiate_mutex);

    self_component_id = component_id;
  } else if (state == NICE_COMPONENT_STATE_FAILED) {
    g_main_loop_quit (gloop);
  }
}
