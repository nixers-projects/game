#include <stdio.h>

#include "game.h"
#include "entity.h"
#include "util.h"

#ifndef ASSETS
	#define ASSETS "assets/"
#endif

void game_init(SDL_Renderer *ren) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entities[i] = NULL;
    }

	char* path = buildPath(ASSETS, "sprites/stickman.bmp");

    character = CreateEntity(ren, 100, 100, 64,128,path);
    character->type = ENTITY_TYPE_MAIN_CHARACTER;
    entities[0] = character;
    entities[1] = CreateEntity(ren, 200, 200, 64,128,path);
    entities[2] = CreateEntity(ren,400,50,64,128,path);
	free(path);
}
