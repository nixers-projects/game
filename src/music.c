#include <err.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Music * loadMusic(char path[])
{
    Mix_Music * music = Mix_LoadMUS(path);

    if (music == NULL) {
        errx(1, "Failed to load music\nSDL ERROR: %s", SDL_GetError());
    }

    return music;
}

void playMusic(Mix_Music * music)
{
    Mix_PlayMusic(music, 1);
}

void toggleMusic()
{
    if(Mix_PausedMusic()) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}

void cleanUp(Mix_Music * music)
{
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}
