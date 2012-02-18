CPPFLAGS ?= -Wall -O2
PREFIX   ?= usr/local

CPPFLAGS += -Iinclude

objects = src/fastpurge.o
sources = src/fastpurge.cpp

bin    := $(DESTDIR)/$(PREFIX)/bin

fastpurge: $(objects) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $(objects)

.cpp.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean: 
	rm -f $(objects) fastpurge

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: clean install
