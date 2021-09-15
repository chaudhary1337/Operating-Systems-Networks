#include "all.h"

/*
handles my own written commands
*/
int handle_my_command(char *args[MAX_ARGS])
{
    if (strncmp(args[0], "cd", 2) == 0)
    {
        handle_cd(args);
        return 1;
    }

    return 0;
}

/*
first parameter is the user input
goal: stores the arguments in the second input parameter as a list of strings
*/
void get_args(char *user_input, char *args[MAX_ARGS])
{
    int i = 0;
    args[i] = strtok(user_input, " ");
    while (args[i])
    {
        args[++i] = strtok(NULL, " ");
    }
}

void handle_input(char *user_input)
{
    char *args[MAX_ARGS];
    get_args(user_input, args);

    // handle my own implemented commands
    int is_my_command = handle_my_command(args);
    if (is_my_command)
        return;

    // if I don't have it implemented, time to call execvp

    int fork_return = fork();
    if (fork_return)
    {
        wait(NULL);
    }
    else
    {
        int exec_return = execvp(args[0], args);
        // if invalid command, print its invalid and exit
        if (exec_return < 0)
        {
            printf("Command \"%s\" not found!\n", user_input);
            exit(0);
        }
    }
    return;
}