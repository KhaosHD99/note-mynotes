###
###     Makefile for FNDemoPhone
###
###             generated for UNIX/LINUX environments
###             by elon
###

BINDIR= bin
#INCDIR= inc
SRCDIR= src
OBJDIR= obj
#CC=gcc
CXX=gcc
#CFLAG += -I inc
FLAG = `pkg-config --cflags --libs gtk+-2.0 libglade-2.0` -export-dynamic
#LINK = g++ -g -Wl --hash-style=sysv

#TARGET = test
OBJ = CDivider.o \
			CUniter.o 
			
# -lFnVpu 
#all: $(TARGET)
#$(TARGET): LinkedList.cpp
all : 
#	$(CXX) CDivider.cpp -o CDivider
	$(CC) test.c -o test $(FLAG)
#$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
#	$(CXX) -MM $(CPPFLAGS) $< > $@.temp;
#	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.temp > $@;
#	rm -f $(OBJDIR)/@.temp

#sinclude $(OBJ:.o=.d) 

#CDivider.o : $(SRCDIR)/CDivider.cpp
#	$(CXX) $(SRCDIR)/CDivider.cpp $(CXXFLAG) -o $(OBJDIR)/CDivider.o

#CUniter.o : $(SRCDIR)/CUniter.cpp 
#	$(CXX) $(SRCDIR)/CUniter.cpp $(CXXFLAG) -o $(OBJDIR)/CUniter.o

#.PHONY: clean
#clean:
#	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.out $(OBJDIR)/*.d
#install-pro:
#	cp $(BINDIR)/$(TARGET) /opt/nfs/rootfs/home/yaoquan/
