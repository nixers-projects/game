#include <stdio.h>

#include "game.h"
#include "entity.h"

void game_init(SDL_Renderer *ren) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entities[i] = NULL;
    }
    entities[0] = CreateEntity(ren, 200, 200, "stickman.bmp");

    character = CreateEntity(ren, 100, 100, "stickman.bmp");
    character->type = ENTITY_TYPE_MAIN_CHARACTER;
}
