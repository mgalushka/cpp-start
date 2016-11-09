export GST_DEBUG=4
./video_phone.o 1 $(host -4 -t A stun.stunprotocol.org | awk '{ print $4 }') 2>&1 ~/cool000.log
