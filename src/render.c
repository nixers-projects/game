#include "render.h"

int rmask = 0xff000000;
int gmask = 0x00ff0000;
int bmask = 0x0000ff00;
int amask = 0x000000ff;

void renderClear(SDL_Renderer *ren) {
    // Clear buffer
    setTargetToBuffer(ren);
    SDL_RenderClear(ren);

    // Clear collision buffer
    setTargetToCollisionBuffer(ren);
    SDL_RenderClear(ren);
}

void renderEntity(SDL_Renderer *ren, entity* e, int color[3]) {
    SDL_Rect bodyRect;
    SDL_Rect textureRect;
    bodyRect.x = e->x;
    bodyRect.y = e->y;
    bodyRect.w = e->w;
    bodyRect.h = e->h;
    textureRect.x = e->x;
    textureRect.y = e->y;
    SDL_QueryTexture(e->curr_img, NULL, NULL, &textureRect.w, &textureRect.h);
    renderToBuffer(ren, e->curr_img, &textureRect);
    renderToCollisionBuffer(ren, &bodyRect, color);
}

void render(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *r, int color[3]) {
    renderToBuffer(ren, tex, r);
    renderToCollisionBuffer(ren, r, color);
}

void renderToBuffer(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *r) {
    if (SDL_SetRenderTarget(ren, buffer) != 0) {
        puts("FUCK BUFFER");
    }
    SDL_RenderCopy(ren, tex, NULL, r);
}

void renderToCollisionBuffer(SDL_Renderer *ren, SDL_Rect *r, int color[3]) {
    if (SDL_SetRenderTarget(ren, collision_buffer) != 0) {
        puts("FUCK COLLISION");
    }
    SDL_Texture *t;
    SDL_Surface *s;

    s = SDL_CreateRGBSurface(0, r->w, r->h, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(s, NULL, SDL_MapRGB(s->format,
                color[0], color[1], color[2]));
    if (s == NULL) printf("FUCK SURFACE %s", SDL_GetError());

    t = SDL_CreateTextureFromSurface(ren, s);
    SDL_RenderCopy(ren, t, NULL, r);
}

int buffers_init(SDL_Renderer *ren) {
    buffer = NULL;
    collision_buffer = NULL;
    buffer = SDL_CreateTexture(ren, 0,
            SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    collision_buffer = SDL_CreateTexture(ren, 0,
            SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (buffer == NULL || collision_buffer == NULL) return 1;
    return 0;
}

void setTargetToCollisionBuffer(SDL_Renderer *ren) {
    if (SDL_SetRenderTarget(ren, collision_buffer) != 0) {
        fprintf(stderr, "Failed to switch Target to collision_buffer");
    }
}

void setTargetToBuffer(SDL_Renderer *ren) {
    if (SDL_SetRenderTarget(ren, buffer) != 0) {
        fprintf(stderr, "Failed to switch Target to buffer");
    }
}
