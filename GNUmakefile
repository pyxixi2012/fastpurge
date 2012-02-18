CPPFLAGS ?= -pedantic -Wall -O2
PREFIX   ?= usr/local

CPPFLAGS += -std=c++0x -Iinclude
LDFLAGS  += -lev

sources  := src/fastpurge.cpp
objects  := $(sources:.cpp=.o)

bin    := $(DESTDIR)/$(PREFIX)/bin

fastpurge: $(objects) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $(objects)

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.deps: $(sources)
	$(CXX) $(CPPFLAGS) -M $(sources) >$@

clean: 
	rm -f $(objects) fastpurge

distclean: clean
	rm -f .deps

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: clean distclean install

ifneq ($(MAKECMDGLOBALS),clean)
ifneq ($(MAKECMDGLOBALS),distclean)
-include .deps
endif
endif
