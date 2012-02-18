CPPFLAGS ?= -Wall -O2
PREFIX   ?= usr/local

CPPFLAGS += -Iinclude

objects = fastpurge.o
sources = src/fastpurge.cpp

bin    := $(DESTDIR)/$(PREFIX)/bin

fastpurge: $(objects) 
	$(CXX) $(CPPFLAGS) -o $@ $(objects)

$(objects): $(sources) 
	$(CXX) $(CPPFLAGS) -c $(sources)

clean: 
	rm -f $(objects) fastpurge

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: clean install
