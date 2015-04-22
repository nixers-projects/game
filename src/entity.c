#include "entity.h"
#include "game.h"
#include "render.h"
#include "collision.h"

entity* CreateEntity(SDL_Renderer *ren, int x, int y, int w, int h,char *imagePath) {
    SDL_Surface *img = SDL_LoadBMP(imagePath);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);

    entity *e = malloc(sizeof(entity));
    e->x = x;
    e->y = y;
    e->w = w;
    e->h = h;
    e->x_vel = 0;
    e->y_vel = 0;
    e->velocity = 50;
    e->curr_img = tex;
    e->type = ENTITY_TYPE_DEFAULT;
    return e;
}

void rendererEntity(SDL_Renderer *ren, entity *e) {
    render(ren, e, (int[3])WORLD_COLOR_HARD);
}

void updateEntity(entity *e, float deltaTimeS) {
    switch (e->type) {
        case ENTITY_TYPE_DEFAULT:
            if (character->x < e->x)  entity_move(e, e->x - e->velocity * deltaTimeS,e->y);
            if (character->x > e->x) entity_move(e,e->x + e->velocity * deltaTimeS,e->y);
            if (character->y < e->y) entity_move(e,e->x,e->y - e->velocity * deltaTimeS);
            if (character->y > e->y) entity_move(e,e->x,e->y + e->velocity * deltaTimeS);
            break;
        case ENTITY_TYPE_MAIN_CHARACTER:
            entity_move(e, e->x + e->x_vel, e->y + e->y_vel);
            break;
        case ENTITY_TYPE_PET:
            if (character->x - 25 < e->x) e->x -= e->velocity * deltaTimeS;
            if (character->x + 25 > e->x) e->x += e->velocity * deltaTimeS;
            if (character->y - 25 < e->y) e->y -= e->velocity * deltaTimeS;
            if (character->y + 25 > e->y) e->y += e->velocity * deltaTimeS;
            break;
        default:
            printf("Invalid entity type");
            break;
    }
}

// Moves entity to new position if possible
void entity_move(entity *e, float x, float y) {
    if(x != e->x)
    {
        SDL_Rect newRect;
        newRect.x = x;
        newRect.y = e->y;
        newRect.w = e->w;
        newRect.h = e->h;
        if(!checkCollision(&newRect,e)) e->x = x;
    }
    if(y != e->y)
    {
        SDL_Rect newRect;
        newRect.x = e->x;
        newRect.y = y;
        newRect.w = e->w;
        newRect.h = e->h;
        if(!checkCollision(&newRect,e)) e->y = y;
    }
}

void entity_move_left(entity *e, float deltaTimeS) {
    e->x_vel = e->velocity * deltaTimeS * -5;
}

void entity_move_right(entity *e, float deltaTimeS) {
    e->x_vel = e->velocity * deltaTimeS * 5;
}
void entity_move_up(entity *e, float deltaTimeS) {
    e->y_vel = e->velocity * deltaTimeS * -5;
}

void entity_move_down(entity *e, float deltaTimeS) {
    e->y_vel = e->velocity * deltaTimeS * 5;
}

void entity_stop(entity* e) {
    e->x_vel = 0;
    e->y_vel = 0;
}
