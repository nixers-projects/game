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

    char* path = buildPath(ASSETS, "sprites/soldier.png");

    SDL_Rect *frames = malloc(sizeof(SDL_Rect) * 4);
    /*SDL_Rect f = { 0, 0, 64, 64 };*/
    frames[0] = (SDL_Rect){ 0, 0, 64, 64 };
    frames[1] = (SDL_Rect){ 64, 0, 64, 64 };
    frames[2] = (SDL_Rect){ 128, 0, 64, 64 };
    frames[3] = (SDL_Rect){ 0, 64, 64, 64};

    SDL_Rect *framestorso = malloc(sizeof(SDL_Rect));
    framestorso[0] = (SDL_Rect){ 64, 64, 64, 64};

    twoPartAnimation tpAnim;
    tpAnim.legs = CreateAnimation(ren, path, frames, 3, 0.2);
    tpAnim.torso = CreateAnimation(ren, path, framestorso, 0, 0.3);

    character = CreateEntity(100, 100, 24,32,tpAnim);
    character->type = ENTITY_TYPE_MAIN_CHARACTER;
    character->velocity = 80;
    character->w = 64;
    character->h = 64;
    entities[0] = character;

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
