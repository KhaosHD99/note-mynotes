XX=gcc
FLAG = `pkg-config --cflags --libs gtk+-2.0 libglade-2.0` -export-dynamic

all :
	$(CC) test.c -o test $(FLAG)

clean: 
	rm -f *.o test
