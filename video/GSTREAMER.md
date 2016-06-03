# Install packages

plugins are taken from here:
https://gstreamer.freedesktop.org/src/gst-plugins-base/
https://gstreamer.freedesktop.org/src/gst-plugins-good/
https://gstreamer.freedesktop.org/src/gst-plugins-bad/


brew install pkg-config
brew install gstreamer
brew install gtk

Check that this command is working:
```
pkg-config --cflags --libs gtk+-2.0 gstreamer-1.0
```

install tremor:

```
git clone https://github.com/soundcloud/tremor.git
./autogen.sh
./configure
make && make install
```

```
cp /usr/local/lib/pkgconfig/vorbisidec.pc /usr/local/lib/pkgconfig/ivorbisidec.pc
```

Then - reinstall gst-plugins-base-1.6.3 plugins in standard way:
```
./configure && make && make install
```
# Debugging

Add `--gst-debug-level=4` flag to gstreamer application

# Webcam

How to stream video from webcam on mac:
```
gst-launch-1.0 wrappercamerabinsrc mode=2  ! video/x-raw, width=320, height=240 ! autovideosink
gst-launch-1.0 wrappercamerabinsrc mode=2  ! video/x-raw, width=320, height=240 ! udpsink host=127.0.0.1 port=1234
```

input video from test
```
gst-launch-1.0 -v videotestsrc ! videoconvert ! avenc_h263p ! rtph263ppay ! udpsink host=127.0.0.1 port=5001
```

input video from webcam
```
gst-launch-1.0 -v wrappercamerabinsrc mode=2  ! video/x-raw, width=320, height=240 ! videoconvert ! avenc_h263p ! rtph263ppay ! udpsink host=127.0.0.1 port=5001
```

You need to copy `caps` from input and pass on receiver:

```
gst-launch-1.0 -v udpsrc address=127.0.0.1 port=5001 caps="application/x-rtp\,\ media\=\(string\)video\,\ clock-rate\=\(int\)90000\,\ encoding-name\=\(string\)H263-1998\,\ payload\=\(int\)96\,\ ssrc\=\(uint\)870888106\,\ timestamp-offset\=\(uint\)3238251667\,\ seqnum-offset\=\(uint\)8585" ! rtph263pdepay ! avdec_h263 ! autovideosink
```


Watch video from internet:
```
gst-launch-1.0 playbin uri=http://docs.gstreamer.com/media/sintel_trailer-480p.webm
```

# Debugging

```
brew install gdb
sudo gdb ./ice_streaming_sample.o
```
Go through this process to codesign gdb:
http://www.patosai.com/blog/post/installing-gdb-on-mac-os-x-yosemite

In gdb session:
```
set scheduler-locking on
b ice_streaming_sample.c:232
b ice_streaming_sample.c:336
b ice_streaming_sample.c:389
b ice_streaming_sample.c:407
run 0 $(host -4 -t A stun.stunprotocol.org | awk '{ print $4 }') --gst-debug-level=5
```