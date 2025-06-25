/*
 * Access to SunTile's display
 * See render.h for documentation
 * 2025 DJaySky
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#include <sds.h>

#include "render.h"

// == Local variables ==========================================
SDL_Renderer *rend;

/// An intermediate RGB struct
struct RGB {
	int r;
	int g;
	int b;
};

// == Color helper functions ===================================
/// Converts a hex color (what is defined in the Color struct)
/// into an RGB struct that SDL can use.
///
/// Parameters:
/// - col: The color to be converted to RGB
///
/// Returns:
/// An RGB struct with the hex color converted to RGB values.
struct RGB hex_to_rgb(Color col) {
	struct RGB out;
	out.r = (col >> 16) & 0xFF;
	out.g = (col >> 8) & 0xFF;
	out.b = col & 0xFF;
	return out;
}

// == Render modifying functions ===============================
void render_clear(Color col) {
	struct RGB rgb = hex_to_rgb(col);
	SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
	SDL_RenderClear(rend);
}

void render_pix(int x, int y, Color col) {
	struct RGB rgb = hex_to_rgb(col);
	SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);
	SDL_RenderPoint(rend, x, y);
}

void render_rect(int x, int y, int sx, int sy, bool fill, Color col) {
	struct RGB rgb = hex_to_rgb(col);
	SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);

	SDL_FRect rect;
	rect.x = x;
	rect.y = y;
	rect.w = sx-x;
	rect.h = sy-y;

	if(fill) {
		SDL_RenderFillRect(rend, &rect);
	} else {
		SDL_RenderRect(rend, &rect);
	}
}

void render_line(int x, int y, int x1, int y1, Color col) {
	struct RGB rgb = hex_to_rgb(col);
	SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);

	int dx = abs(x1 - x);
	int dy = abs(y1 - y);
	int sx = x < x1 ? 1 : -1;
	int sy = y < y1 ? 1 : -1;
	int err = dx - dy;

	int x2 = x;
	int y2 = y;

	while(true) {
		SDL_RenderPoint(rend, x2, y2);

		if(x2 == x1 && y2 == y1) break;

		int e2 = 2 * err;
		if(e2 > -dy) {
			err -= dy;
			x2 += sx;
		}

		if(e2 < dx) {
			err += dx;
			y2 += sy;
		}
	}
}

void render_circ(int x, int y, int radius, bool fill, Color col) {
	struct RGB rgb = hex_to_rgb(col);
	SDL_SetRenderDrawColor(rend, rgb.r, rgb.g, rgb.b, 255);

	if(!fill) {
		int x1 = radius;
		int y1 = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (radius << 1);

		while(x1 >= y1) {
			SDL_RenderPoint(rend, x+x1, y+y1);
			SDL_RenderPoint(rend, x+y1, y+x1);
			SDL_RenderPoint(rend, x-y1, y+x1);
			SDL_RenderPoint(rend, x-x1, y+y1);
			SDL_RenderPoint(rend, x-x1, y-y1);
			SDL_RenderPoint(rend, x-y1, y-x1);
			SDL_RenderPoint(rend, x+y1, y-x1);
			SDL_RenderPoint(rend, x+x1, y-y1);

			if(err <= 0) {
				y1++;
				err += dy;
				dy += 2;
			}

			if(err > 0) {
				x1--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}
	} else {
		for(int y1 =-radius; y1<=radius; y1++) {
			for(int x1=-radius; x1<=radius; x1++) {
				if(x1*x1+y1*y1 <= radius*radius + radius) {
					SDL_RenderPoint(rend, x+x1,y+y1);
				}
			}
		}
	}
}

// == Other Functions ==========================================
void render_scale() {
	render_clear(BLACK);

	SDL_SetRenderLogicalPresentation(
		rend,
		256,
		128,
		SDL_LOGICAL_PRESENTATION_LETTERBOX
	);
}

void window_to_render(float x, float y, float *out_x, float *out_y) {
	SDL_RenderCoordinatesFromWindow(rend, x, y, out_x, out_y);
}

void render_init(SDL_Window *win) {
	rend = SDL_CreateRenderer(win, NULL);
	render_scale();
}

void render_draw() {
	SDL_RenderPresent(rend);
}
