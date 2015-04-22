#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "SDL2/SDL.h"
#include "entity.h"

bool checkCollision(SDL_Rect*,entity*);

#endif  // COLLISION_H
