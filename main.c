#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include "music.h"
#include "image.h"


int main(int argc, char ** argv) {
        int playing = 1;
        if(SDL_Init(SDL_INIT_VIDEO) == -1)
        {
                errx(1, "Failed to initialise SDL\nSDL ERROR: %s", SDL_GetError());
                return 1;
        }
        SDL_Window* win = SDL_CreateWindow("Nixers",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);
        SDL_Surface* screenSurf = SDL_GetWindowSurface(win);
        if(win == NULL)
        {
                errx(1,"Window could not be created\nSDL ERROR: %s",SDL_GetError());
                return 1;
        }
	Mix_Music * music = NULL;
        if(initImg() == false)
        {
                return 1;
        }
	if (initAudio() == false) {
		return 1;
	}
	music = loadMusic("../res/song.mp3");
	playMusic(music);
        SDL_Surface* sprite = loadImage(screenSurf,"../res/rice.jpg");
        if(sprite == NULL)
        {
            return 1;
        }
        SDL_BlitSurface(sprite,NULL,screenSurf,NULL);
        SDL_UpdateWindowSurface(win);

	puts("u dick");
        SDL_Event event;
	while (Mix_PlayingMusic() && playing) {
            while(SDL_PollEvent(&event))
            {
                    switch(event.type)
                    {
                            case SDL_QUIT:
                            playing = 0;
                            case SDL_KEYDOWN:
                            switch(event.key.keysym.sym)
                            {
                                    case SDLK_ESCAPE:
                                    playing = 0;
                            }
                    }
            }
            SDL_UpdateWindowSurface(win);
	}

        SDL_FreeSurface(sprite);
        SDL_FreeSurface(screenSurf);
        SDL_DestroyWindow(win);
	cleanUp(music);

	return 0;
}
