CPPFLAGS ?= -pedantic -Wall -O2
PREFIX   ?= usr/local

CPPFLAGS += -std=c++0x -Iinclude
LDFLAGS  += -lev

sources  := fastpurge.cpp base_adapter.cpp

srcdir   := src/
objdir   := obj/
depdir   := dep/

srcpath  := $(addprefix $(srcdir),$(sources))
objpath  := $(addprefix $(objdir),$(sources:.cpp=.o))
deppath  := $(addprefix $(depdir),$(sources:.cpp=.mk))

bin      := $(DESTDIR)/$(PREFIX)/bin

fastpurge: $(objpath)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(objdir)%.o: $(srcdir)%.cpp $(objdir)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(objdir):
	mkdir -p $@

$(depdir)%.mk: $(srcdir)%.cpp $(depdir)
	$(CXX) $(CPPFLAGS) -M -MF $@ $<

$(depdir):
	mkdir -p $@

clean:
	rm -f -- $(objdir)*.o fastpurge

distclean:
	rm -f -r -- $(objdir) $(depdir)

install: $(bin)/fastpurge

$(bin)/fastpurge: fastpurge $(bin)
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: clean distclean install

ifneq ($(MAKECMDGLOBALS),clean)
ifneq ($(MAKECMDGLOBALS),distclean)
-include $(deppath)
endif
endif
