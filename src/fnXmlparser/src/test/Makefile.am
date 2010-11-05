bin_PROGRAMS=test_xmlparser
test_xmlparser_SOURCES= \
	main.cpp TimeListResolver.cpp play_act.cpp

#LIBS=  -lphoneconfig -lpthread
test_xmlparser_LDFLAGS=-D_GNU_SOURCE -L$(top_srcdir)/src/lib/.libs -lfnxmlparser -lpthread
DEFS+=-D_GNU_SOURCE
#LIBS=-lpthread

