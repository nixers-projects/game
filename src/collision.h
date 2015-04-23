#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "SDL2/SDL.h"
#include "entity.h"

typedef struct {
    SDL_Rect *array;
    size_t used;
    size_t size;
} map_object_arr;

// Saves collision points for map
map_object_arr collision_map;

bool checkCollision(SDL_Rect*,entity*);

// collsision_map stuff
void initMapObjectArr(map_object_arr *a, size_t initialSize);
void insertMapObjectArr(map_object_arr *a, SDL_Rect element);
void freeMapObjectArr(map_object_arr *a);

#endif  // COLLISION_H
