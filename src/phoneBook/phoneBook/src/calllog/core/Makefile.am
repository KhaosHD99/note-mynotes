#noinst_LIBRARIES=libphonebook.a
#libphonebook_a_SOURCES = phonebook.cpp
#INCLUDES=-I../../../include -I../include

   LDFLAGS=-fPIC -shared
   moduledir=$(prefix)/src/calllog/core/
   module_PROGRAMS=calllog.so
   calllog_so_SOURCES=calllog.cpp
   calllog_so_LDFLAGS=-module
   calllog_so_LDADD=../../../lib/liblinconfig.a
   INCLUDES=-I../../../include -I../include
