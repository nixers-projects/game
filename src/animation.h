#include <SDL2/SDL.h>

typedef struct animation {
    int frameNumber,frameWidth,frameHeight,current_frame,startX,startY;
    float elapsedTime,timeBetweenFrames;
} animation;

typedef struct animationCollection {
    animation* idle;
    animation* move_up;
    animation* move_right;
    animation* move_down;
    animation* move_left;
} animationCollection;

animation* CreateAnimation(int frameNumber, int frameWidth, int frameHeight, float timeBetweenFrames, int startX, int  startY);
void updateAnimation(animation* e, float deltaTimeS);
SDL_Rect* getTextureRect(animation*, int texX);
