#ifndef MUSIC
#define MUSIC

bool initAudio();
Mix_Music * loadMusic(char path[]);
void playMusic();
void cleanUp();
void toggleMusic();

#endif
