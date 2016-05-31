PKG_CONFIG_PATH=/usr/local/Cellar/gtk+/2.24.29/lib/pkgconfig/:/usr/local/Cellar/gstreamer/1.6.3/lib/pkgconfig/

CC=gcc

all: internet_video.o

internet_video.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -stdlib=libc++ `pkg-config --cflags --libs gtk+-2.0 gstreamer-1.0` internet_video.c -o internet_video.o

clean:
	rm internet_video.o
