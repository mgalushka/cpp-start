#ifndef VPHONE_VIDEO_H_
#define VPHONE_VIDEO_H_

#include "common.h"
#include "gstreamer_utils.h"

void* _send_video_main (CustomData *data);

void  _send_audio_init_gstreamer(NiceAgent *magent, guint stream_id, CustomData *data);

#endif // VPHONE_VIDEO_H_
