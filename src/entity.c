#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "game.h"
#include "render.h"
#include "collision.h"

entity* CreateEntity(int x, int y, int w, int h, twoPartAnimation tpAnim)
{
    entity *e = malloc(sizeof(entity));
    e->x = x;
    e->y = y;
    e->w = w;
    e->h = h;
    e->x_vel = 0;
    e->y_vel = 0;
    e->velocity = 70;
    e->tpAnim = tpAnim;
    e->type = ENTITY_TYPE_DEFAULT;
    e->torso_angle = 0.0f;
    e->torso_center = (SDL_Point){ 32, 32 };
    return e;
}

void updateEntity(entity *e, float deltaTimeS)
{
    /*updateAnimation(e->anim,deltaTimeS);*/
    updateTpAnimation(&e->tpAnim, deltaTimeS);
    switch (e->type) {
    case ENTITY_TYPE_DEFAULT:
        if (character->x < e->x) entity_move_left(e, deltaTimeS);
        if (character->x > e->x) entity_move_right(e, deltaTimeS);
        if (character->y < e->y) entity_move_up(e, deltaTimeS);
        if (character->y > e->y) entity_move_down(e, deltaTimeS);
        entity_move(e, e->x + e->x_vel, e->y + e->y_vel);
        break;
    case ENTITY_TYPE_MAIN_CHARACTER:
        entity_move(e, e->x + e->x_vel, e->y + e->y_vel);
        break;
    case ENTITY_TYPE_PET:
        if (character->x - 25 < e->x) entity_move_left(e, deltaTimeS);
        if (character->x + 25 > e->x) entity_move_right(e, deltaTimeS);
        if (character->y - 25 < e->y) entity_move_up(e, deltaTimeS);
        if (character->y + 25 > e->y) entity_move_down(e, deltaTimeS);
        entity_move(e, e->x + e->x_vel, e->y + e->y_vel);
        break;
    default:
        printf("Invalid entity type");
        break;
    }
}

// Moves entity to new position if possible
void entity_move(entity *e, float x, float y)
{
    if(x != e->x) {
        SDL_Rect newRect;
        newRect.x = x;
        newRect.y = e->y;
        newRect.w = e->w;
        newRect.h = e->h;
        if(!checkCollision(&newRect,e)) e->x = x;
    }
    if(y != e->y) {
        SDL_Rect newRect;
        newRect.x = e->x;
        newRect.y = y;
        newRect.w = e->w;
        newRect.h = e->h;
        if(!checkCollision(&newRect,e)) e->y = y;
    }
}

void eventEntity(entity * e, SDL_Event event, float deltaTimeS)
{
    if (event.type == SDL_KEYDOWN) {
        SDL_Scancode key = event.key.keysym.scancode;
        if (key == SDL_SCANCODE_A) {
            entity_move_left(e, deltaTimeS);
        } else if (key == SDL_SCANCODE_D) {
            entity_move_right(e, deltaTimeS);
        } else if (key == SDL_SCANCODE_S) {
            entity_move_down(e, deltaTimeS);
        } else if (key == SDL_SCANCODE_W) {
            entity_move_up(e, deltaTimeS);
        }
    } else if(event.type == SDL_KEYUP) {
        SDL_Scancode key = event.key.keysym.scancode;
        if (key == SDL_SCANCODE_A || key == SDL_SCANCODE_D) {
            character->x_vel = 0;
        } else if (key == SDL_SCANCODE_S || key == SDL_SCANCODE_W) {
            character->y_vel = 0;
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        // Check main.c!

        /*int deltaX = event.motion.x + camera.x - (e->x + 32);*/
        /*int deltaY = event.motion.y + camera.y - (e->y + 32);*/
        /*e->torso_angle = atan2(deltaY, deltaX) * 180 / PI;*/
    }
}

void entity_move_left(entity *e, float deltaTimeS)
{
    e->x_vel = e->velocity * -deltaTimeS;
    e->tpAnim.legs->angle = 270;
}

void entity_move_right(entity *e, float deltaTimeS)
{
    e->x_vel = e->velocity * deltaTimeS;
    e->tpAnim.legs->angle = 90;
}
void entity_move_up(entity *e, float deltaTimeS)
{
    e->y_vel = e->velocity * -deltaTimeS;
    e->tpAnim.legs->angle = 0;
}

void entity_move_down(entity *e, float deltaTimeS)
{
    e->y_vel = e->velocity * deltaTimeS;
    e->tpAnim.legs->angle = 180;
}
