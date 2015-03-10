#include <stdio.h>
#include "player.h"

void setName(struct Player player, char * name) {
    player.name = name;
}

char * getName(struct Player player) {
    return player.name;
}
