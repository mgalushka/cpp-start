export GST_DEBUG=5
./video_phone.o 1 $(host -4 -t A stun.stunprotocol.org | awk '{ print $4 }')
