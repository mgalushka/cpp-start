PKG_CONFIG_PATH=/usr/local/Cellar/gtk+/2.24.29/lib/pkgconfig/:/usr/local/Cellar/gstreamer/1.6.3/lib/pkgconfig/

CC=gcc

all: video_phone.o

video_phone.o:
	${CC} 	-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -stdlib=libc++ `pkg-config --cflags --libs gtk+-2.0 gstreamer-1.0 nice` *.c -o video_phone.o

clean:
	rm video_phone.o
