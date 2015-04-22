#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "entity.h"
#include "game.h"
#include "music.h"
#include "util.h"
#include "render.h"

#define WINDOW_TITLE "Game"
#define MAX_FPS 100

#ifndef ASSETS
	#define ASSETS "assets/"
#endif

// Main window
SDL_Window *screen;
SDL_Renderer *renderer;

TTF_Font *font;

SDL_Texture *curr_buffer;

void draw(int deltaTimeMs) {
    float deltaTimeS = (float) deltaTimeMs / 1000;
    float fps = (float) 1.0 / deltaTimeS;

    rendererEntity(renderer, character);
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (entities[i] != NULL)
            rendererEntity(renderer, entities[i]);
    }

    SDL_Color background = { 0, 0, 0, 0 };
    SDL_Color foreground = { 255, 255, 255, 0 };

    char str[10];
    sprintf(str, "%3.2f fps", fps);
    SDL_Surface *textSurface = TTF_RenderText(font, str, foreground, background);
    SDL_Rect textLocation = { 0, 0, 50, 25 };
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    renderToBuffer(renderer, text, &textLocation);
}

void update(int deltaTimeMs) {
    float deltaTimeS = (float) deltaTimeMs / 1000;
    updateEntity(character, deltaTimeS);
    for (int i = 0; i < MAX_ENTITIES; i++) {
        if (entities[i] != NULL)
            updateEntity(entities[i], deltaTimeS);
    }
}

void event(SDL_Event e, int deltaTimeMs) {
    if (e.type == SDL_KEYDOWN) {
        SDL_Scancode key = e.key.keysym.scancode;
        if (key == SDL_SCANCODE_SPACE) {
            toggleMusic();
        } else if (key == SDL_SCANCODE_C) {
            if (curr_buffer == buffer) curr_buffer = collision_buffer;
            else curr_buffer = buffer;
        }
    }
    eventEntity(character, e, (float) deltaTimeMs / 1000);
}

int main(int argc, char **argv) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "Failed to initialize TTF: %s\n", SDL_GetError());
        return 1;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)) {
        fprintf(stderr, "Failed to load Mixer: %s", SDL_GetError());
    }

    screen = SDL_CreateWindow(WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_BORDERLESS);
    if (screen == NULL) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(screen, -1, 0);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }
	
    char* path = buildPath(ASSETS,"fonts/FONT.TTF");
    font = TTF_OpenFont(path, 12);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n",TTF_GetError());
        return 1;
    }
	free(path);

    Mix_Music* music = loadMusic(buildPath(ASSETS,"music/song.mp3"));
    playMusic(music);

    // Black backround
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    game_init();
    if (buffers_init(renderer) != 0) {
        fprintf(stderr, "Failed to craete buffers: %s", SDL_GetError());
        return 1;
    }

    curr_buffer = buffer;
    SDL_Event e;
    SDL_Rect render_rect;
    render_rect.x = 0; render_rect.y = 0;
    render_rect.w = WINDOW_WIDTH;
    render_rect.h = WINDOW_HEIGHT;
    bool quit = false;
    int deltaTime = 0;
    int currentFrame = SDL_GetTicks();
    int lastFrame;
    int fpsMs = 1000 / MAX_FPS;
    while (!quit) {
        lastFrame = currentFrame;
        currentFrame = SDL_GetTicks();
        deltaTime = currentFrame - lastFrame;

        renderClear(renderer);

        update(deltaTime);
        draw(deltaTime);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
            else
                event(e, deltaTime);
        }

        // Reset the target
        SDL_SetRenderTarget(renderer, NULL);
        // Copy the buffer
        SDL_RenderCopy(renderer, curr_buffer, NULL, &render_rect);
        // Draw the buffer to window
        SDL_RenderPresent(renderer);

        // Delay if we are drawing more that 100 fps
        float delay = fpsMs - deltaTime / 1000;
        if (delay > 0) SDL_Delay(delay);
    }

    SDL_Quit();
    return 0;
}
