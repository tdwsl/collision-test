#ifndef ACTOR_H
#define ACTOR_H

enum {
	ACTORTYPE_PLAYER=0,
};

struct actor {
	float x, y, xv, yv;
	int d;
	int type;
};

struct actor *newActor(int x, int y, int type);
void freeActors();
void drawActors(int xo, int yo);
void controlActor(struct actor *a);
void updateActors(int diff);

#endif
