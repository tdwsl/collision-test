#include <SDL2/SDL.h>
#include <stdlib.h>
#include "initSDL.h"
#include "actor.h"
#include "map.h"

struct actor *actors = 0;
int numActors = 0;

struct actor *newActor(int x, int y, int type) {
	numActors++;
	actors = realloc(actors, sizeof(struct actor)*numActors);
	actors[numActors-1] = (struct actor) {
		x, y, 0, 0, 0, type
	};
	return &actors[numActors-1];
}

void drawActors(int xo, int yo) {
	for(int i = 0; i < numActors; i++) {
		struct actor *a = &actors[i];
		SDL_Rect src = (SDL_Rect) {
			a->d*32, a->type*16, 16, 16
		};
		if(a->yv)
			src.x += 16;
		else if(a->xv)
			src.x += 16 * ((int)(a->x)%2);
		for(int x = -1; x <= 1; x++)
			for(int y = -1; y <= 1; y++) {
				SDL_Rect dst = (SDL_Rect) {
					a->x*32-xo+x*mapW*32,
					a->y*32-yo+y*mapH*32,
					32, 32
				};
				SDL_RenderCopy(renderer, actorTex, &src, &dst);
			}
	}
}

void freeActors() {
	free(actors);
	actors = 0;
	numActors = 0;
}

int safe(float dx, float dy) {
	for(int x = floor(dx+0.1); x <= floor(dx+0.9) && safe; x++)
		for(int y = floor(dy+0.1); y <= ceil(dy) && safe; y++) {
			if(map[(y%mapH)*mapW+(x%mapW)])
				return 0;
		}
	return 1;
}

void updateActors(int diff) {
	for(int i = 0; i < numActors; i++) {
		struct actor *a = &actors[i];
		a->yv += 0.0002;
		if(a->yv > 0.2)
			a->yv = 0.2;

		float dx = a->x + a->xv*diff;
		float dy = a->y + a->yv*diff;

		if(safe(dx, a->y))
			a->x = dx;
		if(safe(a->x, dy))
			a->y = dy;
		else if(a->yv > 0)
			a->yv = 0;

		if(a->x < 0)
			a->x += mapW;
		if(a->y < 0)
			a->y += mapH;
		if(a->x >= mapW)
			a->x -= mapW;
		if(a->y >= mapH)
			a->y -= mapH;
	}
}

void controlActor(struct actor *a) {
	const float v = 0.01;
	a->xv = 0;
	/*if(keyboardState[SDL_SCANCODE_UP])
		a->yv = -v;
	if(keyboardState[SDL_SCANCODE_DOWN])
		a->yv = v;*/
	if(keyboardState[SDL_SCANCODE_UP])
		if(!a->yv)
			a->yv = -0.02;
	if(keyboardState[SDL_SCANCODE_LEFT]) {
		a->d = 1;
		a->xv = -v;
	}
	if(keyboardState[SDL_SCANCODE_RIGHT]) {
		a->d = 0;
		a->xv = v;
	}
}
