#source ./exp.sh


export PRX=/home/yaoquan/opt/x86-usr
export PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/share/pkgconfig:$PRX/lib/pkgconfig

export SHARED_INC=/opt/share/inc
export SHARED_LIB=/opt/share/lib

export GTK2_CFLAGS=`pkg-config --cflags gtk+-2.0`                         
export GTK2_LIBS=`pkg-config --libs gtk+-2.0`

export JPEG_CFLAGS=-I/usr/include
export JPEG_LIBS=-ljpeg
#export CFLAGS="-I/opt/mxc/include -I$SHARED_INC"
#export CPPFLAGS="-I/opt/mxc/include -I$SHARED_INC"
#export LDFLAGS="-L$SHARED_LIB -Wl,--rpath-link -Wl,$SHARED_LIB"
#export LIBS="-lstdc++ -ldl -lpthread"

./configure \
	--prefix=$PRX \
	--with-PACKAGE 


