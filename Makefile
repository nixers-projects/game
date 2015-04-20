CC=cc
SRC=.
ASSETS="assets/"
FLAGS=-Wall -Werror -std=c99 -DASSETS='$(ASSETS)' -c -g
LIBS=-lSDL2 -lSDL2_ttf
OBJS=main.o entity.o game.o util.o
OUT=game

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LIBS)

main.o: main.c
	$(CC) $(FLAGS) $(SRC)/main.c

entity.o: entity.h entity.c
	$(CC) $(FLAGS) $(SRC)/entity.c

game.o: game.h game.c
	$(CC) $(FLAGS) $(SRC)/game.c

util.o: util.h util.c
	$(CC) $(FLAGS) $(SRC)/util.c

clean:
	rm -f $(OUT) $(OBJS)
