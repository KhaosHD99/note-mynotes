#noinst_LIBRARIES=libphonebook.a
#libphonebook_a_SOURCES = phonebook.cpp
#INCLUDES=-I../../../include -I../include

   LDFLAGS=-fPIC -shared
   moduledir=$(prefix)/src/contacts/core/
   module_PROGRAMS=contacts.so
   contacts_so_SOURCES=contacts.cpp
   contacts_so_LDFLAGS=-module
   contacts_so_LDADD=../../../lib/liblinconfig.a
   INCLUDES=-I../../../include -I../include