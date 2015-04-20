CC=cc
FLAGS=-std=c99 -lSDL2 -lSDL2_ttf -lSDL2_mixer
FILES=main.c entity.c game.c music.c
OUT=game

build: $(FILES)
	$(CC) -g -Wall $(FLAGS) -o bin/$(OUT) $(FILES)
