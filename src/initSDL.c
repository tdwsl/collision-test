#include <SDL2/SDL.h>
#include <stdlib.h>
#include <assert.h>
#include "initSDL.h"

SDL_Renderer *renderer;
SDL_Window *window;

SDL_Texture *tileset, *actorTex;

SDL_Texture **textures = 0;
int numTextures = 0;

const Uint8 *keyboardState;

SDL_Texture *loadTexture(const char *filename) {
	SDL_Surface *surf = SDL_LoadBMP(filename);
	assert(surf);
	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xff, 0, 0xff));
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
	assert(tex);
	SDL_FreeSurface(surf);
	return tex;
}

void initSDL() {
	assert(SDL_Init(SDL_INIT_EVERYTHING) >= 0);
	assert(window = SDL_CreateWindow("Fortune", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE));
	assert(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE));
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
	keyboardState = SDL_GetKeyboardState(NULL);

	tileset = loadTexture("img/tileset.bmp");
	actorTex = loadTexture("img/actor.bmp");
}

void endSDL() {
	SDL_DestroyTexture(actorTex);
	SDL_DestroyTexture(tileset);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
