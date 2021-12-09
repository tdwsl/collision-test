#include <SDL2/SDL.h>
#include <stdlib.h>
#include "initSDL.h"
#include "map.h"

int *map, mapW, mapH;

void drawMap(int xo, int yo) {
	for(int i = 0; i < mapW*mapH; i++) {
		int t = map[i]-1;
		if(t < 0)
			continue;

		int x = i%mapW, y = i/mapW;

		SDL_Rect src = (SDL_Rect) {
			(t%4)*16, (t/4)*16, 16, 16
		};

		SDL_Rect dst = (SDL_Rect) {
			x*32-xo, y*32-yo, 32, 32
		};

		SDL_RenderCopy(renderer, tileset, &src, &dst);
	}
}

void generateMap() {
	/*mapW = 10+rand()%7;
	mapH = 7+rand()%5;*/
	mapW = 10;
	mapH = 10;
	map = calloc(mapW*mapH, sizeof(int));

	for(int y = 1; y < mapH; y += 2) {
		int x1 = rand()%(mapW-3);
		int x2 = x1 + rand()%(mapW-x1);

		for(int x = 0; x < mapW; x++)
			map[y*mapW+x] = (x>=x1 && x<=x2) ? ((y/2)%2) : !((y/2)%2);
	}
}
