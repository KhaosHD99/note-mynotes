#source ./exp.sh

export PRX=/opt

export HOST_PATH=/opt/fn3/rootfs
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$HOST_PATH$PRX/lib/pkgconfig

export GTK2_CFLAGS=`pkg-config --cflags gtk+-2.0`
export GTK2_LIBS=`pkg-config --libs gtk+-2.0`

./configure \
	--prefix=$PRX \
	--host=arm-linux \
	--with-PACKAGE 


