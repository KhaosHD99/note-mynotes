
CC = gcc

CFLAGS = -Wall			 	
#	-DG_DISABLE_DEPRECATED 	 	\
#	-DGDK_DISABLE_DEPRECATED 	\
#	-DGDK_PIXBUF_DISABLE_DEPRECATED \
#	-DGTK_DISABLE_DEPRECATED

all: main.c 
	$(CC) main.c -o main $(CFLAGS) `pkg-config gtk+-2.0 --cflags --libs` -export-dynamic

clean: 
	rm -f *.o main
