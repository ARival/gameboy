/**
 * This file is released under the UNLICENSE license, the terms of which are
 * provided within the LICENSE file.
 */

#ifndef _FONT_H
#define _FONT_H

#include <SDL2/SDL.h>
#include <stdint.h>

int FontStartup(SDL_Renderer* renderer);
void FontPrint(SDL_Renderer* renderer, const char *restrict text, int x, int y);

#define FONT_BITMAP_WIDTH	60
#define FONT_BITMAP_HEIGHT 	60
#define FONT_CHAR_WIDTH		6
#define FONT_CHAR_HEIGHT	6
#define FONT_COLUMNS		10
#define FONT_RENDER_SCALE	2

/* Colors in ARGB8888 format. */
#define TEXT_FOREGROUND		0xFFFFFFFF
#define TEXT_BACKGROUND 	0x00000000

#endif
