#include "animation.h"
#include <SDL2/SDL_image.h>

animation* CreateAnimation(SDL_Renderer *ren,char *path, int frameNumber, int frameWidth, int frameHeight, float timeBetweenFrames, int startX, int startY)
{
    SDL_Surface *img = IMG_Load(path);
    if(!img) {
        fprintf(stderr,"IMG_Load: %s\n", IMG_GetError());
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    int texX;
    SDL_QueryTexture(tex,NULL,NULL,&texX,NULL);
    animation *anim = malloc(sizeof(animation));
    anim->tex = tex;
    anim->texX = texX;
    anim->frameNumber = frameNumber;
    anim->frameWidth = frameWidth;
    anim->frameHeight = frameHeight;
    anim->current_frame = 0;
    anim->elapsedTime = 0;
    anim->timeBetweenFrames = timeBetweenFrames;
    anim->startX = startX;
    anim->startY = startY;
    return anim;
}

void updateAnimation(animation* anim, float deltaTimeS)
{
    anim->elapsedTime += deltaTimeS;
    if(anim->elapsedTime >= anim->timeBetweenFrames) {
        anim->elapsedTime = 0;
        if(anim->current_frame >= anim->frameNumber - 1) anim->current_frame = 0;
        else anim->current_frame += 1;
    }
}

SDL_Rect* getTextureRect(animation* anim)
{
    SDL_Rect* textureRect = malloc(sizeof(SDL_Rect));
    textureRect->x = anim->startX * anim->frameWidth;
    textureRect->y = anim->startY * anim->frameHeight;
    int count = 0;
    while(count < anim->current_frame) {
        count++;
        textureRect->x += anim->frameWidth;
        if(textureRect->x >= anim->texX) {
            textureRect->x = 0;
            textureRect->y += anim->frameHeight;
        }
    }
    textureRect->w = anim->frameWidth;
    textureRect->h = anim->frameHeight;
    return textureRect;
}
