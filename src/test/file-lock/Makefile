
CC = gcc

CFLAGS = -Wall			 	\
#	-DG_DISABLE_DEPRECATED 	 	\
#	-DGDK_DISABLE_DEPRECATED 	\
#	-DGDK_PIXBUF_DISABLE_DEPRECATED \
#	-DGTK_DISABLE_DEPRECATED

all: test test2

test: test.c 
	$(CC) test.c -o test $(CFLAGS)

test2: test2.c
	$(CC) test2.c -o test2 $(CFLAGS)

clean: 
	rm -f *.o test test2
