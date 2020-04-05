SHELL := /bin/bash
.PHONY: all clean

CXXFLAGS += -I$(BOOST_ROOT)include
LDFLAGS  += -L$(BOOST_ROOT)lib
LDLIBS   += -lboost_program_options

CLEAN_FILES = mdl

all: mdl

clean:
	rm -f $(CLEAN_FILES)
