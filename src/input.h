/*
 * Input handling for SunTile
 * 2025 Aethari
 */

#ifndef INPUT_H
#define INPUT_H

// == Functions ================================================
/// Retrieves the mouse's current position. The position
/// variables are updated when the mouse moves.
///
/// Parameters:
/// - x, y: Pointers to floats that will be filled with the
///         mouse's position
void input_get_mouse_pos(float *x, float *y);

/// Retrieves the mouse's button state for a specified button.
///
/// Parameters:
/// - btn: An integer index representing which mouse button to
///        get the state of.
///
///        - 1: left click
///        - 2: right click
///        - 3: middle click
bool input_get_mouse_button(int btn);

/// Handles input events, both for SDL (window quits,
/// resizes, etc.) and states for keyboard and mouse inputs.
///
/// Returns:
/// A boolean value representing whether SunTile should
/// keep running or not. If false, closes the window
/// and stops the process.
bool input_update();

#endif
