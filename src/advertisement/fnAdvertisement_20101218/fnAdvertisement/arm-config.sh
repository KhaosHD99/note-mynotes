
export PRX="$HOME/opt"
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:$PRX/lib/pkgconfig

./configure \
  --prefix=$PRX
# --host=arm-linux
