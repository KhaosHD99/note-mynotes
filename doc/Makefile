###
###     Makefile for FNDemoPhone
###
###             generated for UNIX/LINUX environments
###             by WYQ
###

BINDIR= bin
INCDIR= inc
SRCDIR= src
OBJDIR= obj
CC=gcc
CXX=g++
CFLAG += -I inc
LINK = g++ -g -Wl --hash-style=sysv

TARGET = DemoPhone
OBJ = Main.o \
			NetClass.o \
			NetTest.o \
			NetPhone.o \
			NetCtl.o \
			netver.o \
			FNVer.o \
			public.o
			
# -lFnVpu 
all: $(TARGET)
$(TARGET): $(OBJ) /usr/local/lib/
	$(LINK) $(OBJDIR)/*.o -o $(BINDIR)/$(TARGET) -s -lpthread $(INCDIR)/libconfigtools.a

$(OBJDIR)/%.d: $(SRCDIR)/%.cpp
	$(CXX) -MM $(CPPFLAGS) $< > $@.temp;
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.temp > $@;
#	rm -f $(OBJDIR)/@.temp

sinclude $(OBJ:.o=.d) 

%.o: $(SRCDIR)/%.cpp
	$(CXX)  $(CFLAG) -g -c -o2 $< -o $(OBJDIR)/$@

%.o: $(SRCDIR)/%.c 
	$(CC)   $(CFLAG) -g -c -o2 $< -o $(OBJDIR)/$@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/*.out $(OBJDIR)/*.d
install-pro:
	cp $(BINDIR)/$(TARGET) /opt/nfs/rootfs/home/yaoquan/
