#include <SDL2/SDL.h>

typedef struct animation {
    int frameNumber,frameWidth,frameHeight,current_frame;
    float elapsedTime,timeBetweenFrames;
} animation;

animation CreateAnimation(SDL_Renderer* ren,char* imagePath,int frameNumber,int frameWidth,int frameHeight);
void updateAnimation(animation* e,float deltaTimeS,int texX,int texY);
