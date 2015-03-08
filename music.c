#include <err.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

bool initAudio() {
	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
		errx(1, "Failed to initialise SDL\nSDL ERROR: %s", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)) {
		errx(1, "Failed to load SDL_Mixer\nSDL ERROR: %s", SDL_GetError());
		return false;
	}

	return true;
}

Mix_Music * loadMusic(char path[]) {
	Mix_Music * music = Mix_LoadMUS(path);

	if (music == NULL) {
		errx(1, "Failed to load music\nSDL ERROR: %s", SDL_GetError());
	}

	return music;
}

void playMusic(Mix_Music * music) {
	Mix_PlayMusic(music, 1);
}

void cleanUp(Mix_Music * music) {
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
}
