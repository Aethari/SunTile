/*
 * Handles access, saving, and loading of the tilemap
 * 2025 Aethari
 */

#ifndef TILEMAP_H
#define TILEMAP_H

void tilemap_set_tile(int x, int y, int tile);
int tilemap_get_tile(int x, int y);

void tilemap_load(sds path);
void tilemap_save();

#endif
