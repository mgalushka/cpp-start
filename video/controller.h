#ifndef VPHONE_CONTROLLER_H_
#define VPHONE_CONTROLLER_H_

#include "common.h"

void controller_receiver (NiceAgent *agent,
                           guint stream_id,
                           guint component_id,
                           guint len,
                           gchar *buf,
                           gpointer data);
/*
 * 1. Create agent
 * 2. Create stream_id
 * 3. Set receiver
 * 4. Wait until send_audio done
 * 5. Start gathering candidate
 */
void*  controller (CustomData *data);


void set_receiver ( NiceAgent *agent,
                    guint stream_id,
                    GMainContext *context);

void controller_receiver (  NiceAgent *agent,
                            guint stream_id,
                            guint component_id,
                            guint len,
                            gchar *buf,
                            gpointer data);

#endif // VPHONE_CONTROLLER_H_
