#include <SDL2/SDL_image.h>
#include "animation.h"
#include "util.h"

#ifndef ASSETS
#define ASSETS "assets/"
#endif


static SDL_Surface* loadImage(char *path)
{
    SDL_Surface *img = IMG_Load(path);
    if(!img) {
        fprintf(stderr,"IMG_Load: %s\n", IMG_GetError());
        return NULL;
    }
    SDL_SetColorKey(img, 1, SDL_MapRGB(img->format, 255, 0, 255));
    return img;
}


void animationLoadAssets(SDL_Renderer *ren)
{
    char *path = buildPath(ASSETS, "sprites/held_weapons.png");
    SDL_Surface *img = loadImage(path);

    TextureWeapons = SDL_CreateTextureFromSurface(ren, img);

    path = buildPath(ASSETS, "sprites/soldier.png");
    img = loadImage(path);
    TextureSoldier = SDL_CreateTextureFromSurface(ren, img);

    WeaponSMG = (heldWeapon) {
        (SDL_Rect) { 64, 0, 64, 64 },
        5, -15
    };

    free(path);
    SDL_FreeSurface(img);
}

animation* CreateAnimation(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *frames,
                           int numFrames, float timeBetweenFrames)
{
    animation *anim = malloc(sizeof(animation));
    anim->tex = tex;
    anim->numFrames = numFrames;
    anim->currentFrame = 0;
    anim->elapsedTime = 0;
    anim->timeBetweenFrames = timeBetweenFrames;
    anim->frames = frames;

    return anim;
}

void updateAnimation(animation* anim, float deltaTimeS)
{
    anim->elapsedTime += deltaTimeS;
    if(anim->elapsedTime >= anim->timeBetweenFrames) {
        anim->elapsedTime = 0;
        if (anim->currentFrame >= anim->numFrames)  anim->currentFrame = 0;
        else anim->currentFrame += 1;
    }
}
