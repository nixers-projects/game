#include <err.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "music.h"

int main(int argc, char ** argv) {
	Mix_Music * music = NULL;

	if (initAudio() == false) {
		return 1;
	}

	music = loadMusic("res/song.wav");
	playMusic(music);

	puts("u dick");

	while (Mix_PlayingMusic()) {
		SDL_Delay(1);
	}

	cleanUp(music);

	return 0;
}
