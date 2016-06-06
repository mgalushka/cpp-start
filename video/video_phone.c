#include "common.h"
#include "libnice_initialize.h"
#include "gstreamer_utils.h"
#include "send_video.h"

int main(int argc, char *argv[]) {

  if (argc > 4 || argc < 2 || argv[1][1] != '\0') {
    fprintf(stderr, "Usage: %s 0|1 stun_addr [stun_port]\n", argv[0]);
    return EXIT_FAILURE;
  }
  controlling = argv[1][0] - '0';
  if (controlling != 0 && controlling != 1) {
    fprintf(stderr, "Usage: %s 0|1 stun_addr [stun_port]\n", argv[0]);
    return EXIT_FAILURE;
  }

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
