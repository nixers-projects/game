#include "animation.h"
#include <SDL2/SDL_image.h>

animation CreateAnimation(SDL_Renderer *ren,char *imagePath,int frameNumber,int frameWidth,int frameHeight)
{

    animation anim;
    anim.frameNumber = frameNumber;
    anim.frameWidth = frameWidth;
    anim.frameHeight = frameHeight;
    anim.current_frame = 0;
    anim.elapsedTime = 0;
    anim.timeBetweenFrames = 0;
    // printf("%d\n",anim.frameNumber);
    return anim;
}

void updateAnimation(animation* anim,float deltaTimeS,int texX,int texY)
{
    anim->elapsedTime += deltaTimeS;
    if(anim->elapsedTime >= anim->timeBetweenFrames)
    {
        anim->elapsedTime = 0;
        if(anim->current_frame * anim->frameWidth >= texX - anim->frameWidth) anim->current_frame = 0;
        else anim->current_frame += 1;
    }
}
