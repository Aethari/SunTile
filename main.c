/*
 * SunTile entry point/core loops
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <sds.h>

#include "input.h"
#include "render.h"

#include "ui.h"

#ifdef __unix__
	#include <unistd.h>
#elif _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#endif

#define PATH_MAX_LEN 2048
#define VERSION "0.0.0 (alpha)"

// == Functions =================================================
/// Parses command line arguments, handling them and providing
/// output appropriately.
void parse_argument(char *arg) {
	// version | -v or --version
	if(
		strcmp(arg, "-v") == 0 ||
		strcmp(arg, "--version") == 0
	) {
		printf("SunTile version %s\n", VERSION);
		printf("2025 Aethari\n");
		printf("https://github.com/Aethari/SunTile\n");
		exit(0);
	// help | -h or --help
	} else if(
		strcmp(arg, "-h") == 0 ||
		strcmp(arg, "--help") == 0
	) {
		printf("Usage: sunTile [options]\n");
		printf("Tilemap editor for the Sun16 framework\n\n");

		printf("For the SunTile source, see https://github.com/Aethari/SunTile\n");
		printf("For the Sun16 source, seee https://github.com/Aethari/Sun16\n\n");

		printf("  -f                Specify an existing map to load. If left empty,\n");
		printf("                    creates a new, empty map at\n");
		printf("                    \"<working directory>/tilemap.sdat\"\n");
		printf("  -v, --version     Display version information\n");
		printf("  -h, --help        Display this help menu\n\n");

		printf("Multiple command line options can be used at once.\n");
		printf("Whichever option was first will be used.\n\n");

		printf("Examples:\n");
		printf("  sunTile -v\n");
		printf("  sunTile --version\n");
		printf("  sunTile -f /home/user/MyGame/assets/tilemap.sdat");

		printf("\n");
		exit(0);
	} else {
		printf("Command line argument \"%s\" not recognized.\n", arg);
		printf("Use \"sunTile -h\" for more information.\n");
		exit(1);
	}
}

/// Entry point.
int main(int argc, char *argv[]) {
	sds map_path;

	if(argc > 1) {
		for(int i = 1; i < argc; i++) {
			// load tilemap | -f
			// couldn't be in parse_argument() because it needs to
			// look ahead
			if(strcmp(argv[i], "-f") == 0) {
				printf("loading tilemap (not really)...\n");

				if(i != argc-1) {
					map_path = sdsnew(argv[i+1]);

					sds temp_path = sdsdup(map_path);
					sdsrange(temp_path, -4, -1);

					if(strcmp(temp_path, "sdat") != 0) {
						printf("Error (main.c): Provided file is not in .sdat format\n");
						sdsfree(temp_path);
						exit(1);
					}

					char first_char = map_path[0];
					char second_char = map_path[1];

					if(
						first_char != '/' &&
						!(
							isupper(first_char) &&
							second_char == ':'
						)
					) {
						sds temp = sdsdup(map_path);
						
						char* cwd_0 = SDL_GetCurrentDirectory();
						map_path = sdsnew(cwd_0);
						map_path = sdscat(map_path, temp);

						SDL_free(cwd_0);
						sdsfree(temp);
					}

					printf("\n");
				} else {
					char* cwd_0 = SDL_GetCurrentDirectory();
					map_path = sdsnew(cwd_0);
					map_path = sdscat(map_path, "tilemap.sdat");
					SDL_free(cwd_0);
				}

				break;
			} else {
				parse_argument(argv[i]);
			}
		}
	} else {
		char* cwd_0 = SDL_GetCurrentDirectory();
		map_path = sdsnew(cwd_0);
		map_path = sdscat(map_path, "tilemap.sdat");
	}

	printf("SunTile version %s\n", VERSION);
	printf("2025 Aethari\n");
	printf("https://github.com/Aethari/SunTile\n");
	printf("====================================\n\n");

	// setup SDL
	SDL_Window *window;
	bool running = true;

	SDL_Init(
		SDL_INIT_AUDIO |
		SDL_INIT_VIDEO |
		SDL_INIT_JOYSTICK |
		SDL_INIT_EVENTS
	);

	window = SDL_CreateWindow(
		"SunTile - A tile editor for Sun16",
		1024,
		512,
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE
	);

	// setup rendering
	render_init(window);

	// setup the UI
	ui_init();

	// core loop
	while(running) {
		ui_draw();

		render_draw();
		running = ui_update();
	}

	sdsfree(map_path);
	return 0;
}
