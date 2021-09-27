#include "all.h"
#include "my_command.h"
#include "misc.h"

int handle_my_command(int bg, char *args[MAX_ARGS])
{
    if (!strcmp(args[0], "test"))
    {
        printf("testing ok ...\n");
        return 1;
    }
    else if (!strcmp(args[0], "cd"))
    {
        handle_cd(args);
        return 1;
    }
    else if (!strcmp(args[0], "pwd"))
    {
        handle_pwd();
        return 1;
    }
    else if (!strcmp(args[0], "echo"))
    {
        handle_echo(args);
        return 1;
    }
    else if (!strcmp(args[0], "ls"))
    {
        handle_ls(args);
        return 1;
    }
    else if (!strcmp(args[0], "pinfo"))
    {
        handle_pinfo(args);
        return 1;
    }
    else if (!strcmp(args[0], "repeat"))
    {
        handle_repeat(bg, args);
        return 1;
    }
    else if (!strcmp(args[0], "fg"))
    {
        handle_fg(args);
        return 1;
    }
    else if (!strcmp(args[0], "jobs"))
    {
        handle_jobs(args);
        return 1;
    }

    return 0;
}
