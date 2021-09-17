#include "all.h"

extern char home[MAX_PATH_LEN];
extern char prev_path[MAX_PATH_LEN];

// handle tilda path, as in cd ~/src
// same for ./src
void handle_cd(char *args[MAX_ARGS])
{
    if (args[1])
    {
        if (!strcmp(args[1], "-"))
        {
            chdir(prev_path);
            return;
        }
        else if (!strncmp(args[1], "~", 1))
        {
            // first char from str
            memmove(args[1], args[1] + 1, strlen(args[1]));
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
                puts("Some cd-ing error happened. Sad.");
            }
        }
    }
    else
    {
        puts("You want to cd. But, WHERE DO I GO, idiot?");
    }
    return;
}
