#ifndef GAME_H
#define GAME_H

#include <tmx.h>
#include "entity.h"

#define MAX_ENTITIES 100

tmx_map *map;
SDL_Rect map_rect;

entity *entities[MAX_ENTITIES];
entity *character;

void game_init();

#endif  // GAME_H
