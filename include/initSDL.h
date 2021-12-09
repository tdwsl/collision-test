#ifndef INITSDL_H
#define INITSDL_H

#include <SDL2/SDL.h>

extern SDL_Renderer *renderer;
extern SDL_Window *window;

extern SDL_Texture *tileset, *actorTex;

extern const Uint8 *keyboardState;

void initSDL();
void endSDL();

#endif
