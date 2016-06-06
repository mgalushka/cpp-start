#include "send_video.h"

void* _send_video_main (CustomData *data)
{
  data->agent = libnice_create_NiceAgent_with_gstreamer ( send_audio_gathering_done,
                              data->context);

  // Create a new stream with one component
  data->stream_id = libnice_create_stream_id (data->agent);

  while((*receive_audio_gathering_done) == FALSE)
      usleep(100);

  /* Init Gstreamer */
  _send_audio_init_gstreamer(data->agent, data->stream_id, data);

  // Set receiver function
  set_receiver (data->agent, data->stream_id, data->context);

  // Start gathering candidates
  libnice_start_gather_candidate (
    data->agent,
    data->stream_id,
    data->context);
}

void  _send_audio_init_gstreamer(NiceAgent *magent, guint stream_id, CustomData *data)
{
  GstElement *pipeline, *audiotestsrc, *openslessrc, *audioconvert, *caps, *rtpL16pay, *nicesink;
  GstBus *bus;
  GstMessage *msg;
  GstStateChangeReturn ret;
  GSource *bus_source;

  /* Initialize GStreamer */
  gst_init (NULL, NULL);

  source = gst_element_factory_make ("videotestsrc", "source");
  videoconvert = gst_element_factory_make ("videoconvert", "convert");
  h263p = gst_element_factory_make ("avenc_h263p", "h263p");
  rtph263ppay = gst_element_factory_make ("rtph263ppay", "rtph263ppay");
  sink = gst_element_factory_make ("nicesink", "sink");

  /*
  // TODO: think about passing caps
  g_object_set (caps, "caps", gst_caps_from_string("audio/x-raw-int,"
      " channels=1, rate=16000, payload=96"), NULL);
  */

  //Set properties
  g_object_set (sink, "agent", magent, NULL);
  g_object_set (sink, "stream", stream_id, NULL);
  g_object_set (sink, "component", 1, NULL);


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

  bus = gst_element_get_bus (pipeline);
  gst_bus_enable_sync_message_emission (bus);
  gst_bus_add_signal_watch (bus);

  g_signal_connect (bus, "message::error",
      (GCallback) on_error, NULL);

  data->pipeline = pipeline;
  gst_element_set_state(data->pipeline, GST_STATE_PLAYING);
}
