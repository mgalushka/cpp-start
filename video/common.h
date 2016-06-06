#ifndef VPHONE_COMMON_H_
#define VPHONE_COMMON_H_

#include <gst/gst.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <agent.h>

#define STUNSR_ADDR  "107.23.150.92"
#define STUNSR_PORT 3478
#define CONTROLLING_MODE 1
#define CONTROLLED_MODE 0

GMainLoop *gloop;

gboolean *controller_gathering_done;
gboolean *video_send_gathering_done;

typedef struct _CustomData {
  GstElement *pipeline;
  GMainContext *context;
  gboolean initialized;
  GstElement *video_sink;
  GstBus *bus;
  NiceAgent *agent;
  guint stream_id;
  gchar *stun_ip_address;
  guint stun_port;
  guint controlling_mode;
} CustomData;

void __init();

#endif /* VPHONE_COMMON_H_ */
