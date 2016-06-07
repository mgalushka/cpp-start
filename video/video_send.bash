export GST_DEBUG=2
./video_phone.o 0 $(host -4 -t A stun.stunprotocol.org | awk '{ print $4 }')
