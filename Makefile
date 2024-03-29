#
# Copyright (c) 2022 jdeokkim
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

.PHONY: all clean

_COLOR_BEGIN := $(shell tput setaf 13)
_COLOR_END := $(shell tput sgr0)

RAYLIB_PATH ?= $(PROJECT_PATH)/lib/raylib
RAYGUI_PATH ?= $(PROJECT_PATH)/lib/raygui

# TODO: Change the values of `PROJECT_NAME` and `PROJECT_FULL_NAME`
PROJECT_NAME := leko
PROJECT_FULL_NAME := c-krit/leko

PROJECT_PATH := $(PROJECT_NAME)
PROJECT_PREFIX := $(_COLOR_BEGIN)$(PROJECT_FULL_NAME):$(_COLOR_END)

BINARY_PATH := $(PROJECT_PATH)/bin

INCLUDE_PATH := \
	$(PROJECT_PATH)/include \
	$(RAYLIB_PATH)/src      \
	$(RAYGUI_PATH)/src

LIBRARY_PATH := \
	$(PROJECT_PATH)/lib \
	$(RAYLIB_PATH)/src

RESOURCE_PATH := $(PROJECT_PATH)/res
SOURCE_PATH := $(PROJECT_PATH)/src

INCLUDE_PATH += $(SOURCE_PATH)/external

SOURCES := \
	$(SOURCE_PATH)/game.c    \
	$(SOURCE_PATH)/loader.c  \
	$(SOURCE_PATH)/screen.c  \
	$(SOURCE_PATH)/select.c  \
	$(SOURCE_PATH)/title.c   \
	$(SOURCE_PATH)/ui.c      \
	$(SOURCE_PATH)/main.c

OBJECTS := $(SOURCES:.c=.o)

# TODO: Edit the line below if you want another name for your executable
TARGETS := $(BINARY_PATH)/$(PROJECT_PATH)

HOST_PLATFORM := UNKNOWN

ifeq ($(OS),Windows_NT)
	ifeq "$(findstring ;,$(PATH))" ";"
		PROJECT_PREFIX := $(PROJECT_FULL_NAME):
	endif

# MINGW-W64 or MSYS2...?
	HOST_PLATFORM := WINDOWS
else
	UNAME = $(shell uname 2>/dev/null)

	ifeq ($(UNAME),Linux)
		HOST_PLATFORM = LINUX
	endif
endif

CC := gcc
CFLAGS := -D_DEFAULT_SOURCE -g $(INCLUDE_PATH:%=-I%) -O2 -std=gnu99
LDFLAGS := $(LIBRARY_PATH:%=-L%)
LDLIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

CFLAGS += -I$(FEROX_PATH)/ferox/include
LDFLAGS += -L$(FEROX_PATH)/ferox/lib

PLATFORM := $(HOST_PLATFORM)

ifeq ($(PLATFORM),WINDOWS)
	TARGETS := $(BINARY_PATH)/$(PROJECT_PATH).exe

	ifneq ($(HOST_PLATFORM),WINDOWS)
		CC := x86_64-w64-mingw32-gcc
	endif

	LDLIBS := -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
else ifeq ($(PLATFORM),WEB)
	TARGETS := $(BINARY_PATH)/$(PROJECT_PATH).html

	CC := emcc

# https://github.com/emscripten-core/emscripten/blob/main/src/settings.js
	WEBFLAGS := -s ASYNCIFY -s FORCE_FILESYSTEM -s INITIAL_MEMORY=67108864 -s USE_GLFW=3
	WEBFLAGS += --preload-file $(RESOURCE_PATH) --shell-file $(RESOURCE_PATH)/html/shell.html
endif

all: pre-build build post-build

pre-build:
	@echo "$(PROJECT_PREFIX) Using: '$(CC)' to build this project."
    
build: $(TARGETS)

$(SOURCE_PATH)/%.o: $(SOURCE_PATH)/%.c
	@echo "$(PROJECT_PREFIX) Compiling: $@ (from $<)"
	@$(CC) -c $< -o $@ $(CFLAGS)
    
$(TARGETS): $(OBJECTS)
	@mkdir -p $(BINARY_PATH)
	@echo "$(PROJECT_PREFIX) Linking: $(TARGETS)"
	@$(CC) $(OBJECTS) -o $(TARGETS) $(LDFLAGS) $(LDLIBS) $(WEBFLAGS)
    
post-build:
	@echo "$(PROJECT_PREFIX) Build complete."

clean:
	@echo "$(PROJECT_PREFIX) Cleaning up."
	@rm -rf $(BINARY_PATH)/*
	@rm -rf $(SOURCE_PATH)/*.o