#ifndef _INSPECTOR_H
#define _INSPECTOR_H

#include <SDL2/SDL.h>

void InspectorStartup();
void InspectorClick(int x, int y);
void InspectorDraw(SDL_Renderer* renderer);

#endif // _INSPECTOR_H
