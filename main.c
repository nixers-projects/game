#include <stdio.h>

#include "player.h"

int main(int argc, char ** argv) {
	struct Player player;
	char * name;

	puts("      GAME\n    by iotek\n----------------");
	puts("What is your name?\r");
	scanf("%s", player.name);
	setName(player, name);
	printf("Welcome, %s\n", getName(player));

	return 0;
}
