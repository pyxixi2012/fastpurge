CPPFLAGS ?= -Wall -O2 -Iinclude
PREFIX   ?= usr/local

objects = fastpurge.o
sources = src/fastpurge.cpp

fastpurge: $(objects) 
	g++ $(CPPFLAGS) -o fastpurge $(objects)

$(objects): $(sources) 
	g++ $(CPPFLAGS) -c $(sources)

fastpurge.cpp: include/BaseAdapter.h

clean: rm $(objects) fastpurge

bin    := $(DESTDIR)/$(PREFIX)/bin

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: install
