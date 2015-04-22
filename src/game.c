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

    int w,h;
    SDL_Surface *img = SDL_LoadBMP(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
    SDL_QueryTexture(tex,NULL,NULL,&w,&h);
    character = CreateEntity(ren, 100, 100, w,h,path);
    character->type = ENTITY_TYPE_MAIN_CHARACTER;
    character->velocity = 80;
    entities[0] = character;
    entities[1] = CreateEntity(ren, 200, 200, w,h,path);
    entities[2] = CreateEntity(ren,400,50,w,h,path);
	free(path);
}
