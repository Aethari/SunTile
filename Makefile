# Makefile for building, testing, and installing SunTile.
# See README.md for more information about the project.
# See LICENSE.txt for license info.

# == START USER MODIFICATIONS ==================================
# You may change any of the settings below to suit your environment.
# Please do not try to push custom changes that differ from the 
# default to the repository.

# The compiler to use. For cross-platform development/testing,
# different variables for Unix and Windows are used.
CC = gcc
CC_WIN = x86_64-w64-mingw32-gcc

# == END USER MODIFICATIONS ====================================
# Anything beyond this point is not very user-friendly and should 
# not be touched by a normal user, unless you want to add support
# for additional platforms.

# Hide "Entered directory" and "Exited directory" messages
MAKEFLAGS += --no-print-directory

# All of the C files that need to be compiled
SRCS = main.c \
	   lib/*.c \
	   src/*.c

# -- Detect OS ------------------------------------------------
UNAME_S = $(shell uname -s)

# Windows
ifeq ($(OS), Windows_NT)
$(info Guessing Windows_NT)

CC = $(CC_WIN)

all: build-win
build: build-win
test: test-win
clean: clean-win

# Unix
else
$(info Guessing Unix)

all: build-unix
build: build-unix
test: test-unix
install: install-unix
clean: clean-unix

endif

INCLUDE = -Isrc -Ilib/SDL/include -Ilib/
LINK = -Llib -Lbuild
CFLAGS = -lSDL3 -lm -Wall

# == Unix targets =============================================
build-unix:
	make clean

	mkdir -p build

	cp lib/libSDL3.so.0.2.12 build/libSDL3.so.0.2.12
	ln -s libSDL3.so.0.2.12 build/libSDL3.so.0
	ln -s libSDL3.so.0.2.12 build/libSDL3.so

	cp LICENSE.txt build/LICENSE.txt

	@echo
	@echo Compiling project:
	$(CC) $(SRCS) $(INCLUDE) $(LINK) $(CFLAGS) -g -o build/sunTile

test-unix:
	make

	@echo Running project:
	@echo build/sunTile
	@echo
	@build/sunTile

install-unix:
	make
	cp build/sunTile /usr/bin/sunTile

clean-unix:
	@mkdir -p build
	rm -fr build

# == Windows targets ==========================================
build-win:
	make clean

	@echo mkdir build
	@cmd /C "if not exist build mkdir build"

	@echo copy /Y "lib/SDL3.dll" "build/SDL3.dll"
	@cmd /C "copy /Y "lib\\SDL3.dll" "build\\SDL3.dll" > nul"

	@echo copy /Y "LICENSE.txt" "build/LICENSE.txt"
	@cmd /C "copy /Y "LICENSE.txt" "build\\LICENSE.txt" > nul"

	@echo
	@echo Compiling project:
	$(CC) $(SRCS) $(INCLUDE) $(LINK) $(CFLAGS) -o build/sunTile.exe

test-win:
	make

	@echo Running project:
	@echo build/sunTile.exe
	@echo
	@../build/sunTile.exe

clean-win:
	@cmd /C "if not exist "build" mkdir build"

	@echo rmdir /s /q build
	@cmd /C "rmdir /s /q build"
