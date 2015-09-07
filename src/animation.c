#include "animation.h"
#include <SDL2/SDL_image.h>

animation* CreateAnimation(SDL_Renderer *ren, char *path, SDL_Rect *frames,
        int numFrames, float timeBetweenFrames)
{
    SDL_Surface *img = IMG_Load(path);
    if(!img) {
        fprintf(stderr,"IMG_Load: %s\n", IMG_GetError());
    }
    SDL_SetColorKey(img, 1, SDL_MapRGB(img->format, 255, 0, 255));
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    /*int texX;*/
    /*SDL_QueryTexture(tex,NULL,NULL,&texX,NULL);*/
    animation *anim = malloc(sizeof(animation));
    anim->tex = tex;
    /*anim->numFrames = sizeof(frames) / sizeof(SDL_Rect);*/
    anim->numFrames = numFrames;
    anim->currentFrame = 0;
    anim->elapsedTime = 0;
    anim->timeBetweenFrames = timeBetweenFrames;
    anim->frames = frames;

    printf("numFrames %d\n", anim->numFrames);
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

    /*SDL_Rect *r = &anim->frames[anim->currentFrame];*/
    /*printf("x: %d y: %d w: %d h: %d\n", r->x, r->y, r->w, r->h);*/
}

void updateTpAnimation(twoPartAnimation *anim, float deltaTimeS) {
    updateAnimation(anim->legs, deltaTimeS);
    updateAnimation(anim->torso, deltaTimeS);
}
