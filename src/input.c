/*
 * Input handling for SunTile
 * See input.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "render.h"

// == Local variables ==========================================
float mouse_pos_x = 0;
float mouse_pos_y = 0;

bool mouse_1_pressed = false;
bool mouse_2_pressed = false;
bool mouse_3_pressed = false;

// == Fuctions =================================================
void input_get_mouse_pos(float *x, float *y) {
	*x = mouse_pos_x;
	*y = mouse_pos_y;
}

bool input_get_mouse_button(int btn) {
	switch(btn) {
		case 1:
			return mouse_1_pressed;
		case 2:
			return mouse_2_pressed;
		case 3:
			return mouse_3_pressed;
		default:
			return false;
	}
}

bool input_update() {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_EVENT_MOUSE_MOTION:
				SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				switch(event.button.button) {
					case SDL_BUTTON_LEFT:
						mouse_1_pressed = true;
						break;
					case SDL_BUTTON_RIGHT:
						mouse_2_pressed = true;
						break;
					case SDL_BUTTON_MIDDLE:
						mouse_3_pressed = true;
						break;
				}
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				switch(event.button.button) {
					case SDL_BUTTON_LEFT:
						mouse_1_pressed = false;
						break;
					case SDL_BUTTON_RIGHT:
						mouse_2_pressed = false;
						break;
					case SDL_BUTTON_MIDDLE:
						mouse_3_pressed = false;
						break;
				}
				break;
			case SDL_EVENT_QUIT:
				return false;
				break;
			case SDL_EVENT_WINDOW_RESIZED:
				render_scale();
				break;
		}
	}

	return true;
}
