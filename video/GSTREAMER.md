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

# Webcam

How to gstrem video from webcam on mac:

```
gst-launch-1.0 wrappercamerabinsrc mode=2  ! video/x-raw, width=320, height=240 ! autovideosink
gst-launch-1.0 wrappercamerabinsrc mode=2  ! video/x-raw, width=320, height=240 ! udpsink host=127.0.0.1 port=1234

```