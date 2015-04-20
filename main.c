#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "entity.h"
#include "game.h"
#include "music.h"
#include "util.h"

#define WINDOW_TITLE "Game"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define MAX_FPS 100

#ifndef ASSETS
	#define ASSETS "assets/"
#endif

// Main surface
SDL_Window *screen;
SDL_Renderer *renderer;

TTF_Font *font;

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
    SDL_RenderCopy(renderer, text, NULL, &textLocation);
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
    float deltaTimeS = (float) deltaTimeMs / 1000;
    if (e.type == SDL_KEYDOWN) {
        SDL_Scancode key = e.key.keysym.scancode;
        if (key == SDL_SCANCODE_A) {
            entity_move_left(character, deltaTimeS);
        } else if (key == SDL_SCANCODE_D) {
            entity_move_right(character, deltaTimeS);
        } else if (key == SDL_SCANCODE_S) {
            entity_move_down(character, deltaTimeS);
        } else if (key == SDL_SCANCODE_W) {
            entity_move_up(character, deltaTimeS);
        } else if (key == SDL_SCANCODE_SPACE) {
            toggleMusic();
        }   
    } else if(e.type == SDL_KEYUP) {
        SDL_Scancode key = e.key.keysym.scancode;
        if (key == SDL_SCANCODE_A || key == SDL_SCANCODE_D) {
            character->x_vel = 0;
        } else if (key == SDL_SCANCODE_S || key == SDL_SCANCODE_W) {
            character->y_vel = 0;
        }
    }
}

int main(int argc, char **argv) {

    printf("%d\n", argc);
    for (int i = 0; i < argc; i++) {
        /*huehue*/
        printf("%s\n", argv[i]);
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "Failed to initialize TTF: %s\n", SDL_GetError());
        return 1;
    }
    initAudio();

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

    SDL_Event e;
    bool quit = false;
    int deltaTime = 0;
    int currentFrame = SDL_GetTicks();
    int lastFrame;
    int fpsMs = 1000 / MAX_FPS;
    while (!quit) {
        lastFrame = currentFrame;
        currentFrame = SDL_GetTicks();
        deltaTime = currentFrame - lastFrame;

        SDL_RenderClear(renderer);

        update(deltaTime);
        draw(deltaTime);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
            else
                event(e, deltaTime);
        }

        SDL_RenderPresent(renderer);

        // Delay if we are drawing more that 100 fps
        float delay = fpsMs - deltaTime / 1000;
        if (delay > 0) SDL_Delay(delay);
    }

    SDL_Quit();
    return 0;
}
