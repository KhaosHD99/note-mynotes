AUTOMAKE_OPTIONS=foreign
# fun 1
# static lib
# noinst_LIBRARIES = XXX.a
# libXXX_a_LIBADD = @LIBOBJS@ @ALLOCA@
# libXXX_a_SOURCES = XXX.cpp

# fun 2
# share la lib(libtools, configure.in SET AC_PROG_LIBTOOL)
# lib_LTLIBRARIES = XXX.la
# libXXX_la_LIBADD = @LIBOBJS@ @ALLOCA@
# libXXX_la_SOURCES = XXX.cpp


# fun 3
# share so lib
# lib_LTLIBRARIES = XXX.so
# libXXX_so_LIBADD = @LIBOBJS@ @ALLOCA@
# libXXX_so_SOURCES = XXX.cpp
# libXXX_so_LDFLAGS = -fpic -shared

lib_LTLIBRARIES = libfnxmlparser.la
libfnxmlparser_la_SOURCES = \
	XMLInterface.cpp XMLNode.cpp XMLParser.cpp

libfnxmlparser_la_LDFLAGS = -no-undefined -version-info $(LIBFNXMLPARSER_SO_VERSION)

INCLUDES=-I$(top_srcdir)/src/include $(CFLAGS)

fnxmlparserincludedir=$(includedir)/phoneconfig
fnxmlparserinclude_HEADERS=$(top_srcdir)/src/include/XMLInterface.h \
													$(top_srcdir)/src/include/XMLNode.h \
													$(top_srcdir)/src/include/XMLParser.h


