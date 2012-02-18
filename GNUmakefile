CPPFLAGS ?= -pedantic -Wall -O2
PREFIX   ?= usr/local

CPPFLAGS += -std=c++0x -Iinclude
LDFLAGS  += -lev

sources  := src/fastpurge.cpp
objects  := $(sources:.cpp=.o)
depends  := $(sources:.cpp=.dep)

bin    := $(DESTDIR)/$(PREFIX)/bin

fastpurge: $(objects)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $(objects)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

%.dep: %.cpp
	$(CXX) $(CPPFLAGS) -M -MF $@ $<

clean: 
	rm -f $(objects) fastpurge

distclean: clean
	rm -f $(depends)

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: clean distclean install

ifneq ($(MAKECMDGLOBALS),clean)
ifneq ($(MAKECMDGLOBALS),distclean)
-include $(depends)
endif
endif
