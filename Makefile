.ONESHELL:

SHELL := $(shell which bash)

PROJECT_NAME := mdl

CLEAN_FILES = $(PROJECT_NAME)

LDLIBS += -lboost_program_options

# OS
OS_NAME            := $(shell uname -s)
OS_VERSION         := $(shell uname -r)
BOOST_INCLUDE_ROOT :=

## Linux
OS_NAME_LINUX            := Linux
OS_VERSION_MAJOR_BIG_SUR := 20

## Mac
OS_NAME_MAC := Darwin

# Determin Boost directory
ifeq ($(OS_NAME),$(OS_NAME_MAC))
	OS_VERSION_MAJOR := $(shell echo '$(OS_VERSION)' | sed -E 's/($(OS_VERSION_MAJOR_BIG_SUR))\..+/\1/')

	ifeq ($(OS_VERSION_MAJOR),$(OS_VERSION_MAJOR_BIG_SUR))
		BOOST_PREFIX       := $(realpath $(shell brew --prefix boost))
		BOOST_INCLUDE_ROOT := $(realpath $(BOOST_PREFIX)/include)
		BOOST_LIB_ROOT     := $(realpath $(BOOST_PREFIX)/lib)
		CXXFLAGS           += -I$(BOOST_INCLUDE_ROOT)
		LDFLAGS            += -L$(BOOST_LIB_ROOT)
	else
		BOOST_INCLUDE_ROOT := $(realpath /usr/local/include)
	endif
else ifeq ($(OS_NAME),$(OS_NAME_LINUX))
	BOOST_INCLUDE_ROOT := $(realpath /usr/include)
	BOOST_LIB_ROOT     := $(realpath /usr/lib/x86_64-linux-gnu)
	CXXFLAGS           += -I$(BOOST_INCLUDE_ROOT)
	# CFLAGS             += -I$(realpath /usr/include/openssl)
	CXXFLAGS           += -I$(realpath /usr/include/openssl)
	LDFLAGS            += -L$(BOOST_LIB_ROOT)
endif

all: $(PROJECT_NAME)
.PHONY: all

os-name:
	@echo "OS NAME: $(OS_NAME)"
.PHONY: os-name

os-version:
	@echo "OS VERSION: $(OS_VERSION)"
.PHONY: os-version

clean:
	rm -f $(CLEAN_FILES)
.PHONY: clean

