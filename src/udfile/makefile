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
CXX=g++
#CFLAG += -I inc
CXXFLAG = -c
#LINK = g++ -g -Wl --hash-style=sysv

#TARGET = test
OBJ = CDivider.o \
			CUniter.o 
			
# -lFnVpu 
#all: $(TARGET)
#$(TARGET): LinkedList.cpp
divuniter : CDivider.o CUniter.o
#	$(CXX) CDivider.cpp -o CDivider
	$(CXX) $(SRCDIR)/main.cpp $(OBJDIR)/*.o -o $(BINDIR)/DivUniter
#$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
#	$(CXX) -MM $(CPPFLAGS) $< > $@.temp;
#	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.temp > $@;
#	rm -f $(OBJDIR)/@.temp

#sinclude $(OBJ:.o=.d) 

CDivider.o : $(SRCDIR)/CDivider.cpp
	$(CXX) $(SRCDIR)/CDivider.cpp $(CXXFLAG) -o $(OBJDIR)/CDivider.o

CUniter.o : $(SRCDIR)/CUniter.cpp 
	$(CXX) $(SRCDIR)/CUniter.cpp $(CXXFLAG) -o $(OBJDIR)/CUniter.o

#.PHONY: clean
#clean:
#	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.out $(OBJDIR)/*.d
#install-pro:
#	cp $(BINDIR)/$(TARGET) /opt/nfs/rootfs/home/yaoquan/
