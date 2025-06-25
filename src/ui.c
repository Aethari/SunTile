/*
 * SunTile UI implementation
 * Handles both drawing and input events
 * See ui.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "render.h"
#include "input.h"

/// The number of buttons in the toolbar
#define BUTTON_COUNT 8

/*
 * Editor buttons:
 * - paint mode
 * - erase mode
 * - pan mode
 * - eydropper mode
 * - rectangle mode
 * - undo button
 * - redo button
 * - save button
 */

// == Local variables ===========================================
typedef struct Button {
	int x;
	int y;
	int w;
	int h;

	Color bg;
	Color fg;

	bool is_pressed;

	void (* on_pressed)(void);
	void (* on_hover)(struct Button *btn);
	void (* on_leave)(struct Button *btn);
} Button;

Button buttons[BUTTON_COUNT];

sds mode;

// == Button functions ==========================================
void button_hovered(struct Button *btn) {
	btn->bg = DARK_GRAY;
}

void button_on_leave(struct Button *btn) {
	btn->bg = RED;
}

void paint_button_pressed() {
	mode = sdsnew("paint");
}

void erase_button_pressed() {
	mode = sdsnew("erase");
}

void pan_button_pressed() {
	mode = sdsnew("pan");
}

void eyedropper_button_pressed() {
	mode = sdsnew("eyedropper");
}

void rectangle_button_pressed() {
	mode = sdsnew("rectangle");
}

void undo_button_pressed() {
	printf("undo button pressed\n");
}

void redo_button_pressed() {
	printf("redo button pressed\n");
}

void save_button_pressed() {
	printf("save button pressed\n");
}

// == Functions =================================================
void ui_draw() {
	render_clear(BLACK);

	// main editor ui (in green)
	render_rect(1, 1, 11, 255, true, DARK_GREEN);
	render_rect(0, 0, 256, 128, false, GREEN);
	render_line(11, 80, 256, 80, GREEN);
	render_line(11, 0, 11, 128, GREEN);

	// toolbar buttons
	for(int i = 0; i < BUTTON_COUNT; i++) {
		// background
		render_rect(
			buttons[i].x,
			buttons[i].y,
			buttons[i].x + buttons[i].w,
			buttons[i].y + buttons[i].h,
			true,
			buttons[i].bg
		);
	}
}

bool ui_update() {
	bool running = input_update();

	float mouse_win_x = 0, mouse_win_y = 0;
	input_get_mouse_pos(&mouse_win_x, &mouse_win_y);

	float mouse_x = 0, mouse_y = 0;
	window_to_render(mouse_win_x, mouse_win_y, &mouse_x, &mouse_y);

	bool mouse_btn_1 = input_get_mouse_button(1);
	bool mouse_btn_2 = input_get_mouse_button(2);

	// commented to avoid -Wunused-variable
	//bool mouse_btn_3 = input_get_mouse_button(3);

	for(int i = 0; i < BUTTON_COUNT; i++) {
		Button *btn = &buttons[i];

		if(
			mouse_x >= btn->x &&
			mouse_x < btn->x + btn->w &&
			mouse_y >= btn->y &&
			mouse_y < btn->y + btn->h
		) {
			if(mouse_btn_1 || mouse_btn_2) {
				if(!btn->is_pressed) {
					btn->on_pressed();
					btn->is_pressed = true;
				}
			} else {
				btn->on_hover(btn);
				btn->is_pressed = false;
			}
		} else {
			btn->on_leave(btn);
		}
	}

	return running;
}

void ui_init() {
	for(int i = 0; i < BUTTON_COUNT; i++) {
		buttons[i].x = 2;
		buttons[i].w = 8;
		buttons[i].h = 8;
		buttons[i].bg = RED;
		buttons[i].is_pressed = false;
		buttons[i].on_hover = button_hovered;
		buttons[i].on_leave = button_on_leave;
	}

	buttons[0].y = 8;
	buttons[1].y = 23;
	buttons[2].y = 38;
	buttons[3].y = 53;
	buttons[4].y = 68;
	buttons[5].y = 83;
	buttons[6].y = 98;
	buttons[7].y = 113;

	buttons[0].on_pressed = paint_button_pressed;
	buttons[1].on_pressed = erase_button_pressed;
	buttons[2].on_pressed = pan_button_pressed;
	buttons[3].on_pressed = eyedropper_button_pressed;
	buttons[4].on_pressed = rectangle_button_pressed;
	buttons[5].on_pressed = undo_button_pressed;
	buttons[6].on_pressed = redo_button_pressed;
	buttons[7].on_pressed = save_button_pressed;

	mode = sdsnew("paint");
}
