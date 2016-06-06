#include "common.h"

void __init() {

  GST_INFO ("Initializing GStreamer");

  controller_gathering_done = (gboolean *)malloc(sizeof(gboolean));
	*controller_gathering_done = FALSE;

  video_send_gathering_done = (gboolean *)malloc(sizeof(gboolean));
	*video_send_gathering_done = FALSE;

  GST_INFO ("Initialization finished");
}
