#include <SDL2/SDL.h>

#define ANIMATION_MAX_FRAMES 10

typedef struct animation {
    //int frameNumber,frameWidth,frameHeight,current_frame,startX,startY;
    int numFrames;
    int currentFrame;
    SDL_Rect *frames;
    float elapsedTime,timeBetweenFrames;
    SDL_Texture *tex;
    double angle;
    //int texX;
} animation;

typedef struct twoPartAnimation {
    animation *legs;
    animation *torso;
} twoPartAnimation;

// numFrames with zero index
animation* CreateAnimation(SDL_Renderer *ren, char *path, SDL_Rect *frames,
        int numFrames, float timeBetweenFrames);
void updateAnimation(animation* e, float deltaTimeS);
void updateTpAnimation(twoPartAnimation* e, float deltaTimeS);
