#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "entity.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define WORLD_COLOR_HARD { 0, 255, 0 }

SDL_Texture *buffer;
SDL_Texture *collision_buffer;

// 0 success value, negative on error
int buffers_init(SDL_Renderer *ren);

void renderClear(SDL_Renderer*);
void render(SDL_Renderer*, SDL_Texture*, SDL_Rect*, int color[3]);
void renderEntity(SDL_Renderer*, entity*, int color[3]);
void renderToBuffer(SDL_Renderer*, SDL_Texture*, SDL_Rect*);
void renderToCollisionBuffer(SDL_Renderer*, SDL_Rect*, int color[3]);

// If occours any errors, prints to stderr
void setTargetToCollisionBuffer(SDL_Renderer*);
void setTargetToBuffer(SDL_Renderer*);

#endif  // RENDER_H
