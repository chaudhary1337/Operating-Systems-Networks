#include "all.h"

void handle_cd(char *args[MAX_ARGS])
{
    if (args[1])
    {
        int chdir_return = chdir(args[1]);
        if (chdir_return == -1)
        {
            puts("Some cd-ing error happened. Sad.");
        }
    }
    else
    {
        puts("You want to cd. But, WHERE DO I GO, idiot?");
    }
    return;
}