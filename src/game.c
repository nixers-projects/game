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
    entities[0] = CreateEntity(ren, 200, 200, path);

    character = CreateEntity(ren, 100, 100, path);
    character->type = ENTITY_TYPE_MAIN_CHARACTER;
	free(path);
}
