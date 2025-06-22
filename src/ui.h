/*
 * SunTile UI implementation
 * Handles both drawing and input events
 * 2025 Aethari
 */

#ifndef UI_H
#define UI_H

/// Draws the contents of the UI to the screen, using
/// the render library included in render.h.
void ui_draw();

/// Recieves and handles input events.
///
/// Returns:
/// A boolean determining whether or not the program
/// should continue to run. If false, closes the
/// window and stops the process.
bool ui_update();

/// Sets up local UI data. Should be called only
/// once, when the program starts.
void ui_init();

#endif
