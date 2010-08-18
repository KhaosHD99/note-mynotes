###
###     Makefile for FNDemoPhone
###
###             generated for UNIX/LINUX environments
###             by elon
###

BINDIR= bin
INCDIR= include 
OBJDIR= obj
#CC=gcc
CXX=g++
#CFLAG += -I inc
CXXFLAG = -c
#LINK = g++ -g -Wl --hash-style=sysv

#TARGET = test
OBJ = CProdCons.o 
			
all : $(OBJ)
	$(CXX) main.cpp $(OBJDIR)/*.o -I$(INCDIR) -o $(BINDIR)/thread
 
CProdCons.o : 
	$(CXX) $(CXXFLAG) lib/CProdCons.cpp -I$(INCDIR) -o $(OBJDIR)/CProdCons.o


#.PHONY: clean
#clean:
#	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.out $(OBJDIR)/*.d
#install-pro:
#	cp $(BINDIR)/$(TARGET) /opt/nfs/rootfs/home/yaoquan/
