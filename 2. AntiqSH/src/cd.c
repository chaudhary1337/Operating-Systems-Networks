#include "all.h"

extern char home[MAX_PATH_LEN];
extern char prev_path[MAX_PATH_LEN];

/*
handles the cd command.
*/
void handle_cd(char *args[MAX_ARGS])
{
    if (args[1])
    {
        // goto prev path
        if (!strcmp(args[1], "-"))
        {
            chdir(prev_path);
            return;
        }
        // handle if input is compressed with ~ in it
        else if (!strncmp(args[1], "~", 1))
        {
            // yeets first char from str if its '~'
            memmove(args[1], args[1] + 1, strlen(args[1]));
            // puts the home path instead of it
            char expanded_path[MAX_PATH_LEN];
            strcpy(expanded_path, home);
            strcat(expanded_path, args[1]);
            chdir(expanded_path);
            return;
        }
        else
        {
            int chdir_return = chdir(args[1]);
            if (chdir_return == -1)
            {
                puts("check the perms or the name dumass");
            }
        }
    }
    else
    {
        puts("You want to cd. But, WHERE DO I GO, idiot?");
    }
    return;
}
