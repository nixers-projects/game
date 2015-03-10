#ifndef PLAYER
#define PLAYER

struct Player {
	char * name;
	int health;
	int attack;
	int defense;
};

void setName(struct Player player, char * name);
char * getName(struct Player player);

#endif
