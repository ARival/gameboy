/**
 * This file is released under the UNLICENSE license, the terms of which are
 * provided within the LICENSE file.
 */

#include <SDL2/SDL.h>

/* C99 is required for "unsigned long long" (hence uint64_t) support. */
#include <stdint.h>

#include "font.h"

#define FONT_BITMAP_WIDTH	48
#define FONT_BITMAP_HEIGHT 	72
#define FONT_CHAR_WIDTH		6
#define FONT_CHAR_HEIGHT	6
#define FONT_COLUMNS		8

/**
 * 6 x 6 bitmap font for characters ' ' to '~', where each 64-bit value is a
 * line to be on the generated 48x72 font sheet in FontStartup().
 * The 16 most significant bits are unused.
 */
const uint64_t bitmap_font_pixels[72] = {
	0x02089bc514200, 0x011458af94200, 0x000821c500200, 0x0014d28f80000,
	0x0028c9e500200, 0x0000000000000, 0x080000002a210, 0x040000021c408,
	0x020070073e408, 0x010000821c408, 0x008800402a210, 0x0000000000000,
	0x2f0871831821c, 0x2804114424332, 0x240e33c21022a, 0x0212410408226,
	0x020c31033c71c, 0x0000000000000, 0x230401000030c, 0x0408708208492,
	0x221000400070c, 0x0008708208412, 0x020401010040c, 0x0000000000000,
	0x0f3ef9ef1e71c, 0x00820a20a28a0, 0x2c9e7a209efac, 0x08820a20a28aa,
	0x0f02f9ef1e89c, 0x2000000000000, 0x27228824b8722, 0x28a6d82290222,
	0x28aaa8219023e, 0x28b2882292222, 0x072289e48c722, 0x2000000000000,
	0x28a28bef1e71e, 0x28a28880a28a2, 0x2aa288871e89e, 0x2a9488880a482,
	0x0508708792b02, 0x2000000000000, 0x000870271c8a2, 0x0014404110514,
	0x0000408108208, 0x2000410104214, 0x0f8072071c222, 0x0000000000000,
	0x0610010002008, 0x050821060e710, 0x061c51c112480, 0x0408312112480,
	0x030861c60eb00, 0x0000000000000, 0x0000008110204, 0x020c588100004,
	0x0514a8851021c, 0x0514888314224, 0x0214888508224, 0x0000000000000,
	0x0000000000000, 0x089491c61460c, 0x0a9490820c514, 0x0a9490840460c,
	0x0508610604404, 0x0000000000000, 0x0000108400000, 0x0014208218514,
	0x000a600310508, 0x0000208208208, 0x0000108418114, 0x0000000000000
};

/**
 * Context required to store the generated texture with the given renderer.
 */
struct font_ctx_s {
	SDL_Texture *tex;
	SDL_Renderer *rend;
};

font_ctx *FontStartup(SDL_Renderer *renderer, uint32_t fg_col, uint32_t bg_col)
{
	uint32_t *itr;
	SDL_Surface *font_surface;
	SDL_Texture *font_texture;
	font_ctx *ctx;

	font_surface = SDL_CreateRGBSurfaceWithFormat(0,
			FONT_BITMAP_WIDTH, FONT_BITMAP_HEIGHT,
			32, SDL_PIXELFORMAT_ARGB8888);

	if(SDL_LockSurface(font_surface) < 0)
		goto err;

	itr = font_surface->pixels;

	/* Converting bitmap font to font sheet. */
	for (uint_fast8_t y = 0; y < FONT_BITMAP_HEIGHT; y++)
	{
		for (uint_fast8_t x = 0; x < FONT_BITMAP_WIDTH; x++)
		{
			uint_fast8_t bit = (bitmap_font_pixels[y] >> x) & 0x01;
			uint32_t color = (bit ? fg_col : bg_col);
			*(itr++) = color;
		}
	}

	SDL_UnlockSurface(font_surface);
	font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
	SDL_FreeSurface(font_surface);

	if(font_texture == NULL)
		goto err;

	if((ctx = malloc(sizeof(*ctx))) == NULL)
	{
		SDL_DestroyTexture(ctx->tex);
		goto err;
	}

	ctx->tex = font_texture;
	ctx->rend = renderer;

	return ctx;

err:
	return NULL;
}


void FontPrint(font_ctx *ctx, const char *restrict text, int x, int y,
		uint_fast8_t width_scale, uint_fast8_t height_scale)
{
	SDL_Rect font_rect, screen_rect;

	SDL_assert(ctx != NULL);
	SDL_assert(ctx->tex != NULL);
	SDL_assert(ctx->rend != NULL);
	SDL_assert(width_scale > 0);
	SDL_assert(height_scale > 0);

	font_rect.w = FONT_CHAR_WIDTH; 
	font_rect.h = FONT_CHAR_HEIGHT;

	screen_rect.w = FONT_CHAR_WIDTH * width_scale;
	screen_rect.h = FONT_CHAR_HEIGHT * height_scale;
	screen_rect.x = x;
	screen_rect.y = y;

	for (; *text; text++)
	{
		uint_fast8_t pos = *text - ' ';

		font_rect.x = (pos % FONT_COLUMNS) * FONT_CHAR_WIDTH;
		font_rect.y = (pos / FONT_COLUMNS) * FONT_CHAR_HEIGHT;

		SDL_RenderCopy(ctx->rend, ctx->tex, &font_rect, &screen_rect);

		screen_rect.x += screen_rect.w;
	}
}

void FontExit(font_ctx *ctx)
{
	SDL_DestroyTexture(ctx->tex);
	free(ctx);
	ctx = NULL;
}
