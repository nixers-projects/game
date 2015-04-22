CC=cc
SRCDIR=src
ASSETS="assets/"
FLAGS=-Wall -Werror -std=c99 -DASSETS='$(ASSETS)' -c -g
LIBS=-lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -ltmx -ljansson -lxml2 -lz
SRC=$(wildcard $(SRCDIR)/*.c)
OBJS=$(notdir $(SRC:.c=.o))
OUT=game

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LIBS)

%.o: $(SRCDIR)/%.c
	$(CC) $(FLAGS) $<

clean:
	rm -f $(OUT) $(OBJS)
