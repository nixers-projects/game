#include <SDL2/SDL.h>

#define ANIMATION_MAX_FRAMES 10

// TODO: Load all textures globally!
SDL_Texture *TextureWeapons;
SDL_Texture *TextureSoldier;

typedef struct animation {
    int numFrames;
    int currentFrame;
    SDL_Rect *frames;
    float elapsedTime,timeBetweenFrames;
    SDL_Texture *tex;
} animation;

typedef struct twoPartAnimation {
    animation *legs;
    animation *torso;
} twoPartAnimation;

typedef struct heldWeapon {
    SDL_Rect src;
    int x_offset, y_offset;
} heldWeapon;

heldWeapon WeaponSMG;

void animationLoadAssets(SDL_Renderer *ren);

// numFrames with zero index
animation* CreateAnimation(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *frames,
                           int numFrames, float timeBetweenFrames);
void updateAnimation(animation* e, float deltaTimeS);
void updateTpAnimation(twoPartAnimation* e, float deltaTimeS);
