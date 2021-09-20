#include "all.h"
#include "misc.h"

extern char home[MAX_PATH_LEN];
extern char prev_path[MAX_PATH_LEN];

/*
handles the cd command.
*/
void handle_cd(char *args[MAX_ARGS])
{
    int chdir_return;
    if (args[2])
    {
        printf("nana, I only need one arg\n");
        return;
    }
    else if (args[1])
    {
        // goto prev path
        if (!strcmp(args[1], "-"))
        {
            chdir_return = chdir(prev_path);
            return;
        }

        // handle if input is compressed with ~ in it
        if (!strncmp(args[1], "~", 1))
        {
            char expanded_path[MAX_PATH_LEN];
            expand_path(args[1], expanded_path);
            chdir_return = chdir(expanded_path);
        }
        else
        {
            chdir_return = chdir(args[1]);
        }
    }
    else
    {
        chdir_return = chdir(home);
    }

    if (chdir_return == -1)
        puts("check the perms or the name dumass");
    return;
}
