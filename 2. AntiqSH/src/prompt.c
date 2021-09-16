#include "all.h"

char home[256];                // home path
char prev_path[256];           // prev full path
char final_path[256];          // full path, but with ~
char final_path_unmodded[256]; // full path as is

void get_path(char *ans_path, char *final_path_unmodded)
{
    char curr_path[256];
    getcwd(curr_path, sizeof(curr_path));
    strcpy(final_path_unmodded, curr_path);

    // only first time, save the current path in home & prev_path.
    if (!strlen(home))
    {
        strcpy(home, curr_path);
        strcpy(prev_path, curr_path);
    }

    if (strcmp(home, curr_path) == 0)
        strcpy(curr_path, "~\0");

    // if home is present in curr_path, remove it
    else if (strlen(home) < strlen(curr_path) && strstr(curr_path, home))
    {

        char modded_path[256];
        modded_path[0] = '~';
        int j = 1;
        for (int i = strlen(home); i < strlen(curr_path); i++, j++)
            modded_path[j] = curr_path[i];

        modded_path[j] = '\0';
        strcpy(curr_path, modded_path);
    }

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
