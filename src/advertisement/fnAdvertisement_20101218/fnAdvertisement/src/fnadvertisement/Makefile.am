bin_PROGRAMS=fnadvertisement 
#fnadvertisement2
fnadvertisement_SOURCES= \
	main.cpp Advertisement.cpp AdvertisementInterface.cpp TimeListResolver.cpp PlayAct.cpp \
  AdverModule.cpp AdverCcInterface.cpp XMLParser.cpp XMLInterface.cpp
fnadvertisement_LDFLAGS=-D_GNU_SOURCE -L$(top_srcdir)/src/lib/.libs -lfnxmlparser
fnadvertisement_CFLAGS = -DAPP_ONE
fnadvertisement_CPPFLAGS = $(fnadvertisement_CFLAGS)

imgdir=$(prefix)/share/data/appfile/advertisement/image
img_DATA=$(top_srcdir)/src/fnadvertisement/image/*

schemadir=$(prefix)/share/data/appfile/advertisement
schema_DATA=$(top_srcdir)/src/fnadvertisement/myplaylist.xml \
              $(top_srcdir)/src/fnadvertisement/rolltext.xml


#fnadvertisement2_SOURCES= \
#  main.cpp Advertisement.cpp AdvertisementInterface.cpp TimeListResolver.cpp PlayAct.cpp \
#  AdverModule.cpp AdverCcInterface.cpp XMLParser.cpp XMLInterface.cpp
#fnadvertisement2_LDFLAGS=-D_GNU_SOURCE -L$(top_srcdir)/src/lib/.libs -lfnxmlparser
#fnadvertisement2_CFLAGS = -DAPP_TWO
#fnadvertisement2_CPPFLAGS = $(fnadvertisement2_CFLAGS)

#imgdir=/home/data/appfile/skin/advertSkin
#img_DATA=$(top_srcdir)/src/fnadvertisement/image/*


