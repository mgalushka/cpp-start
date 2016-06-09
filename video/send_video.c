#include "send_video.h"

void* _send_video_main (CustomData *data)
{
  /*
  GST_INFO ("Creating libnice agent");
  libnice_create_NiceAgent_with_gstreamer ( video_send_gathering_done, data);
  GST_INFO ("libnice agent created");

  if (data->agent == NULL || data->agent == 0) {
    GST_ERROR ("libnice agent IS NULL!");
    return NULL;
  }

  // Create a new stream with one component
  data->stream_id = libnice_create_stream_id (data->agent, "send_video");
  GST_INFO ("libnice stream_id created");

  // Set receiver function
  set_receiver (data->agent, data->stream_id, data->context);

  // Start gathering candidates
  libnice_start_gather_candidate (
    data->agent,
    data->stream_id,
    data->context);

  g_mutex_lock(&negotiate_mutex);
  while (!negotiation_done) {
    g_cond_wait(&negotiate_cond, &negotiate_mutex);
  }

  g_mutex_unlock(&negotiate_mutex);
  */

  // Init Gstreamer
  _send_video_init_gstreamer(data->agent, data->stream_id, data);

  while(TRUE) {
    usleep(100000);
  }
}

void  _send_video_init_gstreamer(NiceAgent *magent, guint stream_id, CustomData *data)
{
  GstElement *pipeline, *source, *capsfilter, *videoconvert, *h263p, *rtph263ppay, *sink;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  GSource *bus_source;

  GST_INFO ("Pipeline initialization");
  source = gst_element_factory_make ("wrappercamerabinsrc", "source");
  capsfilter = gst_element_factory_make ("capsfilter", "capsfilter");
  videoconvert = gst_element_factory_make ("videoconvert", "convert");
  h263p = gst_element_factory_make ("avenc_h263p", "h263p");
  rtph263ppay = gst_element_factory_make ("rtph263ppay", "rtph263ppay");
  sink = gst_element_factory_make ("udpsink", "sink");

  /*
  // TODO: think about passing caps
  g_object_set (caps, "caps", gst_caps_from_string("audio/x-raw-int,"
      " channels=1, rate=16000, payload=96"), NULL);
  */

  //Set properties
  g_object_set (source, "mode", 2, NULL);
  g_object_set (capsfilter,
                "caps",
                gst_caps_from_string(
                  "video/x-raw, width=320, height=240"), NULL);

  /*
  g_object_set (sink, "agent", magent, NULL);
  g_object_set (sink, "stream", stream_id, NULL);
  g_object_set (sink, "component", 1, NULL);
  */

  g_object_set (sink, "sync", FALSE, NULL);
  g_object_set (sink, "host", "127.0.0.1", NULL);
  g_object_set (sink, "port", 1234, NULL);

  pipeline = gst_pipeline_new ("Video send pipeline");
  if (!pipeline || !source || !videoconvert
      || !h263p || !rtph263ppay || !sink)
  {
    g_printerr ("Not all elements could be created.\n");
    return;
  }

  gst_bin_add_many (GST_BIN (pipeline), source,
            videoconvert, h263p, rtph263ppay,
            sink, NULL);

  if (gst_element_link_many (source, videoconvert, h263p,
                rtph263ppay, sink, NULL) != TRUE)
  {
    g_printerr ("Elements could not be linked.\n");
    gst_object_unref (pipeline);
    return;
  }

  GST_INFO ("Pipeline created, registing on bus");

  bus = gst_element_get_bus (pipeline);
  gst_bus_enable_sync_message_emission (bus);
  gst_bus_add_signal_watch (bus);

  g_signal_connect (bus, "message::error",
      (GCallback) on_error, NULL);

  GST_INFO ("Registing pipeline on bus");

  data->pipeline = pipeline;
  ret = gst_element_set_state(data->pipeline, GST_STATE_PLAYING);

  if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    return;
  } else {
    gchar *sync_caps;
    g_object_get(G_OBJECT(videoconvert), "caps", &sync_caps, NULL);
    GST_ERROR("!!!Caps: %s", sync_caps);
  }
}
