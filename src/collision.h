#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "SDL2/SDL.h"
#include "entity.h"

bool rect_collide_x(SDL_Rect, SDL_Rect);
bool rect_collide_y(SDL_Rect, SDL_Rect);
bool checkCollision(SDL_Rect*,entity*);

#endif  // COLLISION_H
