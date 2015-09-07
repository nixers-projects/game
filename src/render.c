#include <stdio.h>
#include <tmx.h>
#include "render.h"
#include "game.h"
#include "collision.h"

int rmask = 0xff000000;
int gmask = 0x00ff0000;
int bmask = 0x0000ff00;
int amask = 0x000000ff;

void renderClear(SDL_Renderer *ren)
{
    // Clear buffer
    setTargetToBuffer(ren);
    SDL_RenderClear(ren);

    // Clear collision buffer
    setTargetToCollisionBuffer(ren);
    SDL_RenderClear(ren);

    // Draw map collsion buffer to collision buffer
    SDL_RenderCopy(ren, map_collision_buffer, NULL, NULL);
}

void setColor(SDL_Renderer *ren, int color)
{
    unsigned char r, g, b;

    r = (color >> 16) & 0xFF;
    g = (color >>  8) & 0xFF;
    b = (color)       & 0xFF;

    SDL_SetRenderDrawColor(ren, r, g, b, SDL_ALPHA_OPAQUE);
}

void renderEntity(SDL_Renderer *ren, entity* e, int color[3])
{
    SDL_Rect *legsRect = &e->tpAnim.legs->frames[e->tpAnim.legs->currentFrame];
    SDL_Rect *torsoRect = &e->tpAnim.torso->frames[e->tpAnim.torso->currentFrame];
    SDL_Rect bodyRect;

    bodyRect.x = e->x - map_rect.x;
    bodyRect.y = e->y - map_rect.y;
    bodyRect.w = e->w;
    bodyRect.h = e->h;
    SDL_Rect dstrect;
    dstrect.x = e->x;
    dstrect.y = e->y;

    // Legs
    dstrect.w = legsRect->w;
    dstrect.h = legsRect->h;
    renderToBufferEx(ren, e->tpAnim.legs->tex, legsRect, &dstrect,
                     e->tpAnim.legs->angle, NULL);

    // Torso
    dstrect.w = torsoRect->w;
    dstrect.h = torsoRect->h;
    renderToBufferEx(ren, e->tpAnim.torso->tex, torsoRect, &dstrect,
                     e->torso_angle, &e->torso_center);

    renderToCollisionBuffer(ren, NULL, &bodyRect, color);
}

void render(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *srcrect,
            SDL_Rect *dstrect, int color[3])
{
    // NOTE: This doesn't take into account the map's position
    // (see renderEntity)
    renderToBuffer(ren, tex, srcrect, dstrect);
    renderToCollisionBuffer(ren, srcrect, dstrect, color);
}

void renderToBufferEx(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *srcrect,
                      SDL_Rect *dstrect, double angle, SDL_Point *point)
{
    if (SDL_SetRenderTarget(ren, buffer) != 0) {
        puts("FUCK BUFFER");
    }
    SDL_RenderCopyEx(ren, tex, srcrect, dstrect, angle, point, SDL_FLIP_NONE);
}

void renderToBuffer(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *srcrect,
                    SDL_Rect *dstrect)
{
    if (SDL_SetRenderTarget(ren, buffer) != 0) {
        puts("FUCK BUFFER");
    }
    SDL_RenderCopy(ren, tex, srcrect, dstrect);
}

void renderToCollisionBuffer(SDL_Renderer *ren, SDL_Rect *srcrect,
                             SDL_Rect *dstrect, int color[3])
{
    if (SDL_SetRenderTarget(ren, collision_buffer) != 0) {
        puts("FUCK COLLISION");
    }
    SDL_Texture *t = fillRect(ren, dstrect, color);
    SDL_RenderCopy(ren, t, srcrect, dstrect);
}

SDL_Texture* fillRect(SDL_Renderer *ren, SDL_Rect *rect, int color[3])
{
    SDL_Texture *t;
    SDL_Surface *s;

    s = SDL_CreateRGBSurface(0, rect->w, rect->h, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(s, NULL, SDL_MapRGB(s->format,
                                     color[0], color[1], color[2]));
    if (s == NULL) printf("FUCK SURFACE %s", SDL_GetError());

    t = SDL_CreateTextureFromSurface(ren, s);

    return t;
}

int buffers_init(SDL_Renderer *ren)
{
    buffer = NULL;
    collision_buffer = NULL;
    buffer = SDL_CreateTexture(ren, 0,
                               SDL_TEXTUREACCESS_TARGET, map_rect.w, map_rect.h);


    collision_buffer = SDL_CreateTexture(ren, 0,
                                         SDL_TEXTUREACCESS_TARGET, map_rect.w, map_rect.h);



    map_collision_buffer = SDL_CreateTexture(ren, 0,
                           SDL_TEXTUREACCESS_TARGET, map_rect.w, map_rect.h);


    if (buffer == NULL || collision_buffer == NULL
        || map_collision_buffer == NULL)
        return 1;

    return 0;
}

void setTargetToCollisionBuffer(SDL_Renderer *ren)
{
    if (SDL_SetRenderTarget(ren, collision_buffer) != 0) {
        fprintf(stderr, "Failed to switch Target to collision_buffer");
    }
}

void setTargetToBuffer(SDL_Renderer *ren)
{
    if (SDL_SetRenderTarget(ren, buffer) != 0) {
        fprintf(stderr, "Failed to switch Target to buffer");
    }
}

SDL_Texture* renderMap(SDL_Renderer *ren, tmx_map *map)
{
    // Free and re-initialize the collision_map
    freeMapObjectArr(&collision_map);
    initMapObjectArr(&collision_map, 100);

    SDL_Texture *res;
    tmx_layer *layers = map->ly_head;
    int w, h;

    w =  map->width * map->tile_width;
    h =  map->height * map->tile_height;

    if (!(res = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET, w, h)))
        puts("Error while creating map texture");

    if (SDL_SetRenderTarget(ren, res) != 0) puts("FUCK TARGTE");

    setColor(ren, map->backgroundcolor);
    SDL_RenderClear(ren);

    while (layers) {
        if (layers->visible) {
            if (layers->type == L_OBJGR) {
                drawObjects(ren, layers->content.head, layers->color);
            } else if (layers->type == L_IMAGE) {
                drawImageLayer(ren, layers->content.image);
            } else if (layers->type == L_LAYER) {
                drawLayer(ren, res, map, layers);
            }
        }
        layers = layers->next;
    }

    return res;
}

void drawObjects(SDL_Renderer *ren, tmx_object *head, int color)
{
    SDL_Rect rect;
    setColor(ren, color);
    /* FIXME line thickness */
    while (head) {
        if (head->visible) {
            if (head->shape == S_SQUARE) {
                rect.x = head->x;
                rect.y = head->y;
                rect.w = head->width;
                rect.h = head->height;
                SDL_RenderDrawRect(ren, &rect);
            } else if (head->shape  == S_POLYGON) {
                drawPolygon(ren, head->points, head->x, head->y, head->points_len);
            } else if (head->shape == S_POLYLINE) {
                drawPolyline(ren, head->points, head->x, head->y, head->points_len);
            } else if (head->shape == S_ELLIPSE) {
                /* FIXME: no function in SDL2 */
            }
        }
        head = head->next;
    }
}

void drawPolyline(SDL_Renderer *ren, double **points, double x, double y, int pointsc)
{
    int i;
    for (i=1; i<pointsc; i++) {
        SDL_RenderDrawLine(ren, x+points[i-1][0], y+points[i-1][1], x+points[i][0], y+points[i][1]);
    }
}

void drawPolygon(SDL_Renderer *ren, double **points, double x, double y, int pointsc)
{
    drawPolyline(ren, points, x, y, pointsc);
    if (pointsc > 2) {
        SDL_RenderDrawLine(ren, x+points[0][0], y+points[0][1], x+points[pointsc-1][0], y+points[pointsc-1][1]);
    }
}

void drawLayer(SDL_Renderer *ren, SDL_Texture *res, tmx_map *map, tmx_layer *layer)
{
    unsigned long i, j;
    tmx_tileset *ts;
    SDL_Texture *tex_ts;
    SDL_Rect srcrect, dstrect;

    // Clear the map collision buffer
    SDL_SetRenderTarget(ren, map_collision_buffer);
    SDL_RenderClear(ren);
    // Set the target back to map's texture
    SDL_SetRenderTarget(ren, res);

    for (i=0; i<map->height; i++) {
        for (j=0; j<map->width; j++) {
            ts = tmx_get_tileset(map, layer->content.gids[(i*map->width)+j],
                                 // FIXME: This probably aint good way to go..
                                 (unsigned int *)&(srcrect.x),
                                 (unsigned int *)&(srcrect.y));
            if (ts) {
                /* TODO Opacity and Flips */
                srcrect.w = dstrect.w = ts->tile_width;
                srcrect.h = dstrect.h = ts->tile_height;
                dstrect.x = j*ts->tile_width;
                dstrect.y = i*ts->tile_height;
                tex_ts = SDL_CreateTextureFromSurface(ren, (SDL_Surface*)ts->image->resource_image);
                SDL_RenderCopy(ren, tex_ts, &srcrect, &dstrect);
                SDL_DestroyTexture(tex_ts);

                // Following if statement checks which layer we are on
                if (strcmp(layer->name, "solid") == 0) {
                    // While toe following checks which tile (id) we have
                    // if ((layer->content.gids[(i*map->width)+j] & TMX_FLIP_BITS_REMOVAL) == 5) {

                    // Add collision point to collision_map
                    insertMapObjectArr(&collision_map, dstrect);

                    SDL_Texture *tex = fillRect(ren, &dstrect, (int[3])WORLD_COLOR_HARD);

                    SDL_SetRenderTarget(ren, map_collision_buffer);
                    SDL_RenderCopy(ren, tex, NULL, &dstrect);

                    SDL_SetRenderTarget(ren, res);
                    SDL_DestroyTexture(tex);
                }
            }
        }
    }
}

void drawImageLayer(SDL_Renderer *ren, tmx_image *img)
{
    SDL_Surface *bmp;
    SDL_Texture *tex;
    SDL_Rect dim;

    bmp = (SDL_Surface*) img->resource_image;

    dim.x = dim.y = 0;
    dim.w = bmp->w;
    dim.h = bmp->h;

    if ((tex = SDL_CreateTextureFromSurface(ren, bmp))) {
        SDL_RenderCopy(ren, tex, NULL, &dim);
        SDL_DestroyTexture(tex);
    }

}

void updateCamera()
{
    // Move camera
    camera.x = character->x - WINDOW_WIDTH / 2 + character->w / 2;
    camera.y = character->y - WINDOW_HEIGHT / 2;

    // Keep it in bounds
    if (camera.x < 0) camera.x = 0;
    else if (camera.x > map_rect.w - WINDOW_WIDTH)
        camera.x = map_rect.w - WINDOW_WIDTH;
    if (camera.y < 0) camera.y = 0;
    else if (camera.y > map_rect.h - WINDOW_HEIGHT)
        camera.y = map_rect.h - WINDOW_HEIGHT;
}
