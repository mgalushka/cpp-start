# Install packages

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
