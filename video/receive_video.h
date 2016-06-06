#ifndef VPHONE_RECEIVE_VIDEO_H_
#define VPHONE_RECEIVE_VIDEO_H_

#include "common.h"
#include "libnice_initialize.h"
#include "gstreamer_utils.h"

void* _receive_video_main (CustomData *data);
void  _receive_video_init_gstreamer(NiceAgent *magent, guint stream_id, CustomData *data);

#endif // VPHONE_RECEIVE_VIDEO_H_
