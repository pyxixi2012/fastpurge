CPPFLAGS ?= -Wall -O2 -Iinclude
PREFIX   ?= usr/local

objects = fastpurge.o
sources = src/fastpurge.cpp

bin    := $(DESTDIR)/$(PREFIX)/bin

fastpurge: $(objects) 
	g++ $(CPPFLAGS) -o fastpurge $(objects)

$(objects): $(sources) 
	g++ $(CPPFLAGS) -c $(sources)

clean: 
	rm $(objects) fastpurge

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: install
