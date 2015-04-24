#include <stdlib.h>
#include <string.h>

#include "util.h"

char* buildPath(char* root, char* path)
{
    char* full = malloc(strlen(root) + strlen(path) + 1);
    strcpy(full, root);
    strcat(full, path);
    return full;
}
