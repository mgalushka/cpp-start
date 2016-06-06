#include "gstreamer_utils.h"

/* Listen for element's state change */
void on_state_changed (GstBus *bus, GstMessage *msg, CustomData *data)
{
  GstState old_state, new_state, pending_state;
  gst_message_parse_state_changed (msg, &old_state,
                   &new_state,
                   &pending_state);

  if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data->pipeline))
  {
    gchar *message = g_strdup_printf("%s changed to state %s",
             GST_MESSAGE_SRC_NAME(msg),
             gst_element_state_get_name(new_state));
    g_free (message);
  }

  /* Video is ready to play, so display it on surfaceview */
  if (data->pipeline->current_state == GST_STATE_PLAYING)
  {

  }
}

void
on_error (GstBus     *bus,
          GstMessage *message,
          gpointer    user_data)
{
      GError *err;
      gchar *debug_info;
      gchar *message_string;

      gst_message_parse_error (message, &err, &debug_info);

      message_string = g_strdup_printf ("Error received from element %s: %s",
              GST_OBJECT_NAME (message->src), err->message);

      GST_ERROR ("Error received from element %s: %s",
                 GST_OBJECT_NAME (message->src),
                 err->message);

      g_clear_error (&err);
      g_free (debug_info);
      g_free (message_string);
}

/*
void on_pad_added (GstElement* object, GstPad* pad, gpointer data)
{
  gchar *pad_name = gst_pad_get_name(pad);

  GstPad *sinkpad;
  GstElement *autovideosink = (GstElement *) data;
  sinkpad = gst_element_get_static_pad (autovideosink, "sink");
  gst_pad_link (pad, sinkpad);
  gst_object_unref (sinkpad);
}
*/

void set_receiver ( NiceAgent *agent,
                    guint stream_id,
                    GMainContext *context)
{
    nice_agent_attach_recv( agent,
                            stream_id,
                            1,
                            context,
                            controller_receiver,
                            NULL);
}

void controller_receiver (	NiceAgent *agent,
							guint stream_id,
							guint component_id,
							guint len,
							gchar *buf,
							gpointer data)
{
	if (len == 1 && buf[0] == '\0') {
		g_main_loop_quit (gloop);
  }
}
