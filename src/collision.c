#include "SDL2/SDL.h"
#include "collision.h"
#include "game.h"

bool checkCollision(SDL_Rect *rect,entity* self)
{
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if(entities[i] != NULL && entities[i] != self) {
            SDL_Rect r;
            r.x = entities[i]->x;
            r.y = entities[i]->y;
            r.w = entities[i]->w;
            r.h = entities[i]->h;
            if(SDL_HasIntersection(rect,&r)) {
                return true;
            }
        }
    }
    // Check for map collision
    for (int i = 0; i < (int)collision_map.size; i++) {
        if(SDL_HasIntersection(rect, &collision_map.array[i])) {
            return true;
        }
    }
    return false;
}

void initMapObjectArr(map_object_arr *a, size_t initialSize)
{
    a->array = (SDL_Rect *)malloc(initialSize * sizeof(SDL_Rect));
    a->used = 0;
    a->size = initialSize;
}

void insertMapObjectArr(map_object_arr *a, SDL_Rect element)
{
    if (a->used == a->size) {
        a->size *= 2;
        a->array = (SDL_Rect *)realloc(a->array, a->size * sizeof(SDL_Rect));
    }
    a->array[a->used++] = element;
}

void freeMapObjectArr(map_object_arr *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}
