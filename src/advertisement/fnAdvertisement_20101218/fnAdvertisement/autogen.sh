#! /bin/sh
set -x

touch README NEWS AUTHORS ChangeLog

aclocal

libtoolize --force -f -c

autoheader

autoconf

automake --foreign --add-missing --copy


