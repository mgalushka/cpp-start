#include "receive_video.h"

void* _receive_video_main (CustomData *data)
{
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
  while (!exit_thread && !negotiation_done) {
    g_cond_wait(&negotiate_cond, &negotiate_mutex);
  }

  g_mutex_unlock(&negotiate_mutex);

  /* Init Gstreamer */
  _receive_video_init_gstreamer(data->agent, data->stream_id, data);

  while(TRUE) {
    usleep(100000);
  }
}

void  _receive_video_init_gstreamer(NiceAgent *magent, guint stream_id, CustomData *data)
{
  GstElement *pipeline, *source, *sink;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  GSource *bus_source;

  GST_INFO ("Pipeline initialization");
  source = gst_element_factory_make ("nicesrc", "source");
  sink = gst_element_factory_make ("fakesink", "sink");

  g_object_set (source, "agent", magent, NULL);
  g_object_set (source, "stream", stream_id, NULL);
  g_object_set (source, "component", 1, NULL);
  g_object_set (sink, "dump", 1, NULL);


  pipeline = gst_pipeline_new ("Video send pipeline");
  if (!pipeline || !source || !sink) {
    g_printerr ("Not all elements could be created.\n");
    return;
  }

  /* Build the pipeline */
  gst_bin_add_many (GST_BIN (pipeline), source, sink, NULL);
  if (gst_element_link (source, sink) != TRUE) {
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
  }
}
