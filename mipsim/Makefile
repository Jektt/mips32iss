CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11 -Wall -pedantic
LDFLAGS=-g
LDLIBS=

SRCS=mipsim.cpp commands.cpp memory.cpp cache.cpp processor.cpp  
OBJS=$(subst .cpp,.o,$(SRCS))

all: mipsim

mipsim: $(OBJS)
	$(CXX) $(LDFLAGS) -o mipsim $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
