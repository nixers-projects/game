#ifndef GAME_H
#define GAME_H

#include "entity.h"

#define MAX_ENTITIES 100

entity *entities[MAX_ENTITIES];
entity *character;

void game_init();

#endif  // GAME_H
