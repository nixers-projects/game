#include "SDL2/SDL.h"
#include "collision.h"
#include "game.h"

bool checkCollision(SDL_Rect *rect,entity* self)
{
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if(entities[i] != NULL && entities[i] != self)
        {
            SDL_Rect r;
            r.x = entities[i]->x;
            r.y = entities[i]->y;
            r.w = entities[i]->w;
            r.h = entities[i]->h;
            if(SDL_HasIntersection(rect,&r)){
                return true;
            } 
        }
    }
    return false;
}
