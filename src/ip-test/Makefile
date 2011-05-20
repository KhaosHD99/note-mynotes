CC = gcc
CFLAGS = -Wall			 	\
	`pkg-config --cflags --libs gtk+-2.0`

all: test_libpb
test_libpb: test.c 
	$(CC) test.c -o test_libpb $(CFLAGS)

#test2: test2.c
#	$(CC) test2.c -o test2 $(CFLAGS)

clean: 
	rm -f *.o test_libpb
