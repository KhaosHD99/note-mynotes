#!/bin/sh
SUBDIRS = src/lib src/test
CURRENTPATH = $(PWD)
#CURRENTPATH = $(shell /bin/pwd)

INCLUDES = -I$(CURRENTPATH) -I$(CURRENTPATH)/src/include
export INCLUDES

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = fnxmlparser.pc

