#include <gst/gst.h>
  
typedef struct _CustomData {
  gboolean is_live;
  GstElement *pipeline;
  GMainLoop *loop;
} CustomData;
   
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
      g_main_loop_quit (data->loop);
      break;
    }
    case GST_MESSAGE_EOS:
      /* end-of-stream */
      gst_element_set_state (data->pipeline, GST_STATE_READY);
      g_main_loop_quit (data->loop);
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

int main(int argc, char *argv[]) {
  GstElement *pipeline, *source, *sink, *vertigotv;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
   
  /* Initialize GStreamer */
  gst_init (&argc, &argv);
    
  /* Create the elements */
  source = gst_element_factory_make ("videotestsrc", "source");
  vertigotv = gst_element_factory_make ("vertigotv", "effect");
  sink = gst_element_factory_make ("autovideosink", "sink");

  //sink = gst_element_factory_make ("autovideosink", "sink");
    
  /* Create the empty pipeline */
  pipeline = gst_pipeline_new ("test-pipeline");
    
  if (!pipeline || !source || !vertigotv || !sink) {
    g_printerr ("Not all elements could be created.\n");
    return -1;
  }
   
  /* Build the pipeline */
  gst_bin_add_many (GST_BIN (pipeline), source, vertigotv, sink, NULL);
  if (
    gst_element_link (source, vertigotv) != TRUE ||
    gst_element_link (vertigotv, sink) != TRUE
  ) {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (pipeline);
    return -1;
  }
   
  /* Modify the source's properties */
  g_object_set (source, "pattern", 0, NULL);
   
  /* Start playing */
  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    return -1;
  }
   
  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);


  GMainLoop *main_loop;
  CustomData data;

  main_loop = g_main_loop_new (NULL, FALSE);

  data.loop = main_loop;
  data.pipeline = pipeline;
  data.is_live = FALSE;

  gst_bus_add_signal_watch (bus);
  g_signal_connect (bus, "message", G_CALLBACK (cb_message), &data);
  g_main_loop_run (main_loop);

   
  /* Free resources */
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);


  return 0;
}
