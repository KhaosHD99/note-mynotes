echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
echo "个人调试的编译脚本,程序或库将运行在/usr/Fn/debug/$USER"
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
#export SDKDIR=/opt/fn3/mx515_lucid_Compile
export SDKDIR=/opt/fn3/mx515_lucid_dev
export PATH="/opt/fn3/CROSS_BIN:$PATH"
export PKG_CONFIG="/opt/fn3/CROSS_BIN/pkg-config"

export ARMTOOLS=/opt/fn3/armel_gcc/arm-2010q1/bin/arm-none-linux-gnueabi
export CC=$ARMTOOLS-gcc
export CXX=$ARMTOOLS-g++
export LD=$ARMTOOLS-ld
export OBJDUMP=$ARMTOOLS-objdump
export RANLIB=$ARMTOOLS-ranlib
export AS=$ARMTOOLS-as
export AR=$ARMTOOLS-ar
export STRIP=$ARMTOOLS-strip
export NM=$ARMTOOLS-nm

export DEBUG=Fn/debug/$USER
#export DEBUG=Fn/debug
export RELEASE=Fn/release
export SDKDIR_USR=$SDKDIR/usr

export LDFLAGS="-Wl,--rpath -Wl,$SDKDIR/lib  -Wl,--rpath -Wl,$SDKDIR/usr/lib"
export PKG_CONFIG_PATH=$SDKDIR_USR/$DEBUG/lib/pkgconfig:$SDKDIR_USR/$RELEASE/lib/pkgconfig:$SDKDIR_USR/lib/pkgconfig:$SDKDIR/lib/pkgconfig:$SDKDIR_USR/share/pkgconfig:$SDKDIR_USR/Fn/debug/lib/pkgconfig

export PRX=/usr

echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
"echo "make install前, 务必先手工将.libs/XXX.lai的短路径前添加SDKDIR : " $SDKDIR
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

./configure \
  --prefix=$PRX \
  --enable-static=no \
	--build=i686-pc-linux-gnu \
	--host=arm-linux \
	--target=arm-linux \
	--with-install-extern-dir=$DEBUG
