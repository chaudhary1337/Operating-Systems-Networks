#include "all.h"

char home[MAX_PATH_LEN];                // home path
char prev_path[MAX_PATH_LEN];           // prev full path
char final_path[MAX_PATH_LEN];          // full path, but with ~
char final_path_unmodded[MAX_PATH_LEN]; // full path as is

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

void get_path(char *ans_path, char *final_path_unmodded)
{
    char curr_path[MAX_PATH_LEN];
    getcwd(curr_path, sizeof(curr_path));
    strcpy(final_path_unmodded, curr_path);

    // only first time, save the current path in home & prev_path.
    if (!strlen(home))
    {
        strcpy(home, curr_path);
        strcpy(prev_path, curr_path);
    }

    compress_path(curr_path, curr_path);
    strcpy(ans_path, curr_path);
    return;
}

void show_prompt()
{
    char host_name[HOST_NAME_MAX + 1];
    gethostname(host_name, sizeof(host_name));

    strcpy(prev_path, final_path_unmodded); // from the previous execution
    get_path(final_path, final_path_unmodded);
    printf("<%s@%s:%s> ", getenv("USER"), host_name, final_path);
    return;
}
