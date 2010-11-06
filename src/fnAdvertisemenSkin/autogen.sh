#! /bin/sh
set -x

touch README NEWS AUTHORS ChangeLog

aclocal

libtoolize --force -f -c
#share lib 

autoheader

#autoconf

automake --foreign --add-missing --copy

autoconf
