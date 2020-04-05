SHELL := /bin/bash
.PHONY: all clean

LDLIBS += -lboost_program_options

CLEAN_FILES = mdl

all: mdl

clean:
	rm -f $(CLEAN_FILES)

