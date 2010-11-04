
CC = g++

#CFLAGS = -Wall			 	\
#	-DG_DISABLE_DEPRECATED 	 	\
#	-DGDK_DISABLE_DEPRECATED 	\
#	-DGDK_PIXBUF_DISABLE_DEPRECATED \
#	-DGTK_DISABLE_DEPRECATED

#CFLAGS = 

all: main.cpp 
	$(CC) main.cpp config.cpp -o main -Itinyxml tinyxml.o tinyxmlerror.o tinyxmlparser.o tinystr.o
# xmltest.o 
# -Ltinyxml
#$(CFLAGS)
#`pkg-config --cflags --libs gtk+-2.0` -export-dynamic

clean: 
	rm -f *.o main
