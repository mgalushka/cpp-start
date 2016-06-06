#ifndef VPHONE_LIBNICE_UTILS_H_
#define VPHONE_LIBNICE_UTILS_H_

#include "common.h"

void on_state_changed (GstBus *bus,
                       GstMessage *msg,
                       CustomData *data);

void on_error (GstBus     *bus,
               GstMessage *message,
               gpointer    user_data);

/*
void on_pad_added (GstElement* object,
                   GstPad* pad,
                   gpointer data);
*/

void set_receiver (NiceAgent *agent,
                   guint stream_id,
                   GMainContext *context);

void controller_receiver (NiceAgent *agent,
            							guint stream_id,
            							guint component_id,
            							guint len,
            							gchar *buf,
            							gpointer data);

#endif // VPHONE_LIBNICE_UTILS_H_
