CPPFLAGS ?= -Wall
CFLAGS   ?= -pipe -O2
PREFIX   ?= usr/local

fastpurge: fastpurge.c

%: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $^

.c:
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $>

bin    := $(DESTDIR)/$(PREFIX)/bin

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: install
