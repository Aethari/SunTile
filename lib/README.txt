Vendored programs all have their own LICENSE files located in the directory the
source can be found in.

Vendored directories:
	SDL: a mirror of the SDL development repo

Vendored files:
	sds.h, sds.c, sdsalloc.h: a small dynamic string library

Unix dependencies:
	libSDL3.so.0.2.12: dynamic library for SDL

	.so files are symlinked into <name>.so.0 and
	<name>.so within the build directory during the
	build process.

Win dependencies:
	SDL3.dll: dynamic library for SDL
