CPPFLAGS ?= -Wall
CXXFLAGS ?= -pipe -O2
PREFIX   ?= usr/local

fastpurge: fastpurge.cpp

%: %.c++
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

.c++:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $>

bin    := $(DESTDIR)/$(PREFIX)/bin

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: install
