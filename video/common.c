#include "common.h"

void __init() {
  GST_INFO ("Initialization started");
  controller_gathering_done = (gboolean *)malloc(sizeof(gboolean));
	*controller_gathering_done = FALSE;

  video_send_gathering_done = (gboolean *)malloc(sizeof(gboolean));
	*video_send_gathering_done = FALSE;

  io_stdin = g_io_channel_unix_new(fileno(stdin));
  g_io_channel_set_flags (io_stdin, G_IO_FLAG_NONBLOCK, NULL);

  GST_INFO ("Initialization finished");
}
