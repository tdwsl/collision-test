#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "initSDL.h"
#include "map.h"
#include "actor.h"

void draw() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_RenderClear(renderer);
	int xo = w/2 - (mapW*32)/2;
	int yo = h/2 - (mapH*32)/2;
	SDL_Rect r = (SDL_Rect) {
		xo, yo, mapW*32, mapH*32
	};
	SDL_RenderSetViewport(renderer, &r);
	drawMap(0, 0);
	drawActors(0, 0);
	SDL_RenderPresent(renderer);
}

int main() {
	srand(time(NULL));
	initSDL();
	generateMap();
	struct actor *player = newActor(0, 0, ACTORTYPE_PLAYER);
	int quit = 0;
	int lastUpdate = SDL_GetTicks();
	while(!quit) {
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
			switch(ev.type) {
				case SDL_QUIT: quit = 1; break;
			}
		int currentTime = SDL_GetTicks();
		updateActors(currentTime-lastUpdate);
		lastUpdate = currentTime;
		controlActor(player);
		draw();
	}
	freeActors();
	free(map);
	endSDL();
	return 0;
}
