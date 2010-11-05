#export ARMTOOLS=arm-none-linux-gnueabi
#export CC=$ARMTOOLS-gcc 
#export CXX=$ARMTOOLS-g++ 
#export LD=$ARMTOOLS-ld
#export STRIP=$ARMTOOLS-strip

export PRX="$HOME/opt/x86-usr"

export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$PRX/lib/pkgconfig

#arm debug
#####################################
#export PRX=/home/$USER
#export HOST_PATH=/opt/fn3/rootfs

#export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$HOST_PATH/opt/lib/pkgconfig:$HOST_PATH$PRX/lib/pkgconfig
######################################

./configure \
	--prefix=$PRX
#	--host=arm-linux

