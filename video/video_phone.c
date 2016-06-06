#include "common.h"
#include "libnice_initialize.h"
#include "gstreamer_utils.h"
#include "send_video.h"
#include "receive_video.h"

/*
 * To run:
 * ./video_phone.o 0 $(host -4 -t A stun.stunprotocol.org | awk '{ print $4 }') --gst-debug-level=4
 */
int main(int argc, char *argv[]) {

  if (argc > 4 || argc < 2 || argv[1][1] != '\0') {
    fprintf(stderr, "Usage: %s 0|1 stun_addr [stun_port]\n", argv[0]);
    return EXIT_FAILURE;
  }
  gint controlling = argv[1][0] - '0';
  if (controlling != 0 && controlling != 1) {
    fprintf(stderr, "Usage: %s 0|1 stun_addr [stun_port]\n", argv[0]);
    return EXIT_FAILURE;
  }

  gchar *stun_addr = NULL;
  gint stun_port = 3478;
  if (argc > 2) {
    stun_addr = argv[2];
  }

  /* initilize GStreamer and all the data */
  gst_init (&argc, &argv);

  #if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
  #endif

  __init();

  GST_INFO ("Initializing main loop");
  gloop = g_main_loop_new (NULL, FALSE);

  GST_INFO ("Using stun server '[%s]:%u'\n", stun_addr, stun_port);

  CustomData data = {};
  data.context = g_main_loop_get_context (gloop);
  data.stun_ip_address = stun_addr;
  data.stun_port = stun_port;
  data.controlling_mode = controlling;

  GThread *gexamplethread = NULL;

  if (controlling == 0) {
    gexamplethread = g_thread_new("video send thread",
                                  &_send_video_main,
                                  &data);
  } else if (controlling == 1) {
    gexamplethread = g_thread_new("video receive thread",
                                  &_receive_video_main,
                                  &data);
  } else {
    GST_ERROR ("Wrong controlling = %d", controlling);
  }

  g_main_loop_run (gloop);
  g_thread_join (gexamplethread);

  return 0;
}
