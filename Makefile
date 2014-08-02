SHELL := /bin/bash
.PHONY: all clean mdl

CLEAN_FILES = mdl

all: mdl

mdl:mdl.cpp
	g++ -I $${BOOST_ROOT}include/ -L$${BOOST_ROOT}lib/ -lboost_program_options $< -o $@

clean:
	rm -f $(CLEAN_FILES)