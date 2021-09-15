#include "all.h"

/*
handles my own written commands
input: ALL args
return 1 if I had a command for this shit, else nah
*/
int handle_my_command(char *args[MAX_ARGS])
{
    if (!strncmp(args[0], "test", 4))
    {
        printf("testing ok ...\n");
        return 1;
    }
    else if (!strncmp(args[0], "cd", 2))
    {
        handle_cd(args);
        return 1;
    }
    else if (!strncmp(args[0], "re", 2))
    {
        handle_repeat(args);
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

/*
takes care of the arguments and tries to execute them 
input: args
returns: nothing
*/
void handle_command(char *args[MAX_ARGS])
{
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
        // int i = 0;
        // while (args[i])
        // {
        //     printf("trying to exec these dudes: %s\n", args[i]);
        //     i++;
        // }

        // printf("YO WTF, %s", args[i]);
        int exec_return = execvp(args[0], args);
        // printf("\nexec said: %d\n", exec_return);

        // if invalid command, print its invalid and exit
        if (exec_return < 0)
        {
            printf("Command \"%s\" not found.\n", args[0]);
            exit(0);
        }
    }
    return;
}

/*
called by the main function to handle the user input
sends the parsed arguments over to handle_command()
*/
void handle_input(char *user_input)
{
    char *args[MAX_ARGS];
    get_args(user_input, args);
    handle_command(args);
    return;
}
