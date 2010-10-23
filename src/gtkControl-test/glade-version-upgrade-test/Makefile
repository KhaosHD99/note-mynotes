
CC = gcc

#CFLAGS = -Wall			 	\
#	-DG_DISABLE_DEPRECATED 	 	\
#	-DGDK_DISABLE_DEPRECATED 	\
#	-DGDK_PIXBUF_DISABLE_DEPRECATED \
#	-DGTK_DISABLE_DEPRECATED

CFLAGS = 

all: list.c 
	$(CC) list.c -o list $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0` -export-dynamic

clean: 
	rm -f *.o list
