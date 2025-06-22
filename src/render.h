/*
 * Access to SunTile's display
 * 2025 DJaySky
 */

#include <sds.h>

#ifndef RENDER_H
#define RENDER_H

/// Every color that Sun16 supports.
typedef enum {
	BLACK       = 0x000000,
	WHITE       = 0xFFFFFF,
	GRAY        = 0xB2B2B2,
	RED         = 0xCB1717,
	ORANGE      = 0xE58317,
	YELLOW      = 0xE4E91B,
	GREEN       = 0x16CC21,
	BLUE        = 0x1695CC,
	PURPLE      = 0xA416CC,
	BROWN       = 0x823c11,

	DARK_GRAY   = 0x525050,
	DARK_RED    = 0x700D0D,
	DARK_YELLOW = 0xC9B216,
	DARK_GREEN  = 0x206C25,
	DARK_BLUE   = 0x1F3B79,
	DARK_PURPLE = 0x551268
} Color;

// == Render modifying functions ===============================
/// Clears the screen using the color provided.
///
/// Parameters:
/// - col: A Color value that the renderer will be cleared to
void render_clear(Color col);

/// Draws a single pixel on the renderer.
///
/// Parameters:
/// - x,y: The position where the pixel to be drawn
/// - col: A Color value that the pixel will be drawn in
void render_pix(int x, int y, Color col);

/// Draws a rectangle on the renderer.
///
/// Parameters:
/// - x,y: The position of the top left corner of the rectangle
/// - sx,sy: The position of the bottom right corner of the rectangle
/// - fill: Whether or not the rectangle should filled (true for filled)
/// - col: A Color value that the rectangle will be drawn in
void render_rect(int x, int y, int sx, int sy, bool fill, Color col);

/// Draws a line on the renderer, using Bresenham's
/// Line Algorithm.
///
/// Parameters:
/// - x,y: The start point of the line
/// - sx,sy: The end point of the line
/// - col: A Color value that the line will be drawn in
void render_line(int x, int y, int sx, int sy, Color col);

/// Draws a circle on the renderer using the 
/// Midpoint Circle Algorithm.
///
/// Parameters:
/// - x,y: The center point of the circle
/// - radius: The radius (half the width) of the circle
/// - fill: Whether or not the circle should filled (true for filled)
/// - col: A Color value that the circle will be drawn in
void render_circ(int x, int y, int radius, bool fill, Color col);

void render_char(char chr, int x, int y, Color col);
void render_print(sds str, int x, int y, Color col);

// == Other functions ==========================================
/// Recalculates the renderer's scale and applies it
/// using SDL's built in logical presentation. The
/// renderer will be aligned as close as possible to
/// the center of the window.
void render_scale();

/// Converts a window coordinate into the relevant pixel on the
/// renderer. Outputs '-1' if a coordinate is out of bounds.
///
/// Parameters:
/// - x, y: The window coordinates to convert
/// - out_x, out_y: Pointers to variables that will be filled
///                 with the coordinates of the render pixel
void window_to_render(float x, float y, int *out_x, int *out_y);

/// Creates a new SDL_Renderer with size 256*128px,
/// then assigns it to a local variable.
///
/// Parameters:
/// - win: The SDL_Window to attatch the renderer to
void render_init(SDL_Window *win);

/// Draws the current contents of the renderer to
/// the screen, scaling based on the window's size.
void render_draw();

#endif
