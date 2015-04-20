CC=cc
SRC=.
ASSETS="assets/"
FLAGS=-Wall -Werror -std=c99 -DASSETS='$(ASSETS)' -c -g
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_mixer
OBJS=main.o entity.o game.o util.o music.o
OUT=game

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LIBS)

main.o: $(SRC)/main.c
	$(CC) $(FLAGS) $(SRC)/main.c

entity.o: $(SRC)/entity.h $(SRC)/entity.c
	$(CC) $(FLAGS) $(SRC)/entity.c

game.o: $(SRC)/game.h $(SRC)/game.c
	$(CC) $(FLAGS) $(SRC)/game.c

util.o: $(SRC)/util.h $(SRC)/util.c
	$(CC) $(FLAGS) $(SRC)/util.c

music.o: $(SRC)/music.h $(SRC)/music.c
	$(CC) $(FLAGS) $(SRC)/music.c

clean:
	rm -f $(OUT) $(OBJS)
