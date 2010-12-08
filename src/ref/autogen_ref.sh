OK="\\033[70G[\\033[1;32mOK\\033[1;00m]"
FAIL="\\033[70G[\\033[1;31mFAILED\\033[1;00m]"

AUTOGEN_LOG=autogen.log

err ()
{
   echo "-------"
   echo "Error :"
   echo "----------------------------------------"
   cat $AUTOGEN_LOG
   echo "----------------------------------------"
   exit 1
}
 
run ()
{
   echo -n "Running \"$@\""
   eval $@ >$AUTOGEN_LOG 2>&1
   if [ $? = 0 ] ; then
      echo -e $OK
   else
      echo -e $FAIL
      err
   fi
}

###
### cleanning part
###
#  remove autotools stuff
run "rm -rf config"
run "rm -f config.h.in"
run "rm -f aclocal.m4 configure config.log config.status"
run "rm -rf autom4te*.cache"
# remove libtool stuff
run "rm -f libtool"

run "touch README NEWS AUTHORS ChangeLog"
run "aclocal"
run "libtoolize --force --copy"
run "autoheader"
run "autoconf"
run "automake --foreign --add-missing --copy"

