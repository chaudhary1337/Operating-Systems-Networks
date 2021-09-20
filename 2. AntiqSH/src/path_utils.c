#include "all.h"
#include "misc.h"

extern char home[MAX_PATH_LEN];

/*
yeets home from the path if there is home in the path
input: path, compressed final path
*/
void compress_path(char *path, char *compressed_path)
{
    if (strlen(home) <= strlen(path) && strstr(path, home))
    {
        char modded_path[MAX_PATH_LEN] = "\0";
        modded_path[0] = '~';
        int j = 1;
        for (int i = strlen(home); i < strlen(path); i++, j++)
            modded_path[j] = path[i];

        modded_path[j] = '\0';
        strcpy(compressed_path, modded_path);
    }
    else
        strcpy(compressed_path, path);
}

/*
path is extended if ~ is in it.
*/
void expand_path(char *path, char *expanded_path)
{
    // yeets first char from str if its '~'
    memmove(path, path + 1, strlen(path));
    // puts the home path instead of it
    strcpy(expanded_path, "");
    strcpy(expanded_path, home); // put home first
    strcat(expanded_path, path); // then the rest
    return;
}
