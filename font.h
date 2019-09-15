/**
 * This file is released under the UNLICENSE license, the terms of which are
 * provided within the LICENSE file.
 */

#ifndef _FONT_H
#define _FONT_H

#include <SDL2/SDL.h>

typedef struct font_ctx_s font_ctx;

font_ctx *FontStartup(SDL_Renderer *renderer);
void FontPrint(font_ctx *ctx, const char *restrict text, int x, int y);
void FontExit(font_ctx *ctx);

#define FONT_BITMAP_WIDTH	48
#define FONT_BITMAP_HEIGHT 	72
#define FONT_CHAR_WIDTH		6
#define FONT_CHAR_HEIGHT	6
#define FONT_COLUMNS		8
#define FONT_RENDER_SCALE	2

/* Colors in ARGB8888 format. */
#define TEXT_FOREGROUND		0xFFFFFFFF
#define TEXT_BACKGROUND 	0x00000000

/**
 * The following is an example of using this SDL2 font library.
 * Error checking is omitted for brevity.
 * Compile with `gcc $(sdl2-config --libs) font.c example.c`
 */
#if 0
#include <SDL2/SDL.h>
#include "font.h"

int main(void)
{
        SDL_Window *win;
	SDL_Renderer *rend;
	SDL_Surface *surf;
        const char hi[] = "Hello World!";
        font_ctx *ctx;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(320, 240, 0, &win, &rend);
	ctx = FontStartup(rend);
        FontPrint(ctx, hi, 0, 0);
        FontPrint(ctx, hi, 50, 90);
	SDL_RenderPresent(rend);
	SDL_Delay(1000);

        FontExit(ctx);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);

	SDL_Quit();

        return 0;
}
#endif

#endif
