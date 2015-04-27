#include <stdio.h>

#include <SDL2/SDL_image.h>
#include <tmx.h>

#include "game.h"
#include "entity.h"
#include "util.h"
#include "collision.h"

#ifndef ASSETS
#define ASSETS "assets/"
#endif

void game_init(SDL_Renderer *ren)
{
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entities[i] = NULL;
    }

    char* path = buildPath(ASSETS, "sprites/character.png");
    animationCollection collec;
    animation *down = CreateAnimation(ren,path,8,24,32,0.3,0,0);
    animation *up = CreateAnimation(ren,path,8,24,32,0.3,0,1);
    animation *left = CreateAnimation(ren,path,8,24,32,0.3,0,2);
    animation *right = CreateAnimation(ren,path,8,24,32,0.3,0,3);
    collec.move_up = up;
    collec.move_down = down;
    collec.move_left = left;
    collec.move_right = right;
    character = CreateEntity(100, 100, 24,32,collec);
    character->type = ENTITY_TYPE_MAIN_CHARACTER;
    character->velocity = 80;
    entities[0] = character;
    entities[1] = CreateEntity(200, 200, 24,32, collec);
    entities[2] = CreateEntity(400,50,24,32, collec);

    path = buildPath(ASSETS, "map.tmx");
    /* You probably want to create a fuction that creates a SDL_Texture directly here */
    // https://github.com/baylej/tmx/blob/master/examples/sdl.c
    tmx_img_load_func = (void* (*)(const char*))IMG_Load;
    tmx_img_free_func = (void  (*)(void*))      SDL_FreeSurface;

    if (!(map = tmx_load("assets/map.tmx")))
        tmx_perror("tmpx_err");

    map_rect.w = map->width  * map->tile_width;
    map_rect.h = map->height * map->tile_height;
    map_rect.x = 0;
    map_rect.y = 0;

    free(path);
}
