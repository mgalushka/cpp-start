#include "common.h"
#include "libnice_initialize.h"
#include "gstreamer_utils.h"
#include "send_video.h"

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

  gchar *stun_addr;
  gint stun_port;
  if (argc > 2) {
    stun_addr = argv[2];
    if (argc > 3) {
      stun_port = atoi(argv[3]);
    }
    else {
      stun_port = 3478;
    }

    g_debug("Using stun server '[%s]:%u'\n", stun_addr, stun_port);
  }

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  return 0;
}
