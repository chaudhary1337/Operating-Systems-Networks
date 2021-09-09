#include "all.h"

char *MY_COMMANDS[] = {"wow"};
int MAX_ARGS = 16;

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

// int system_command_exec(char *user_input)
// {
//     for (int i = 0; i < sizeof(MY_COMMANDS) / sizeof(MY_COMMANDS[0]); i++)
//     {
//         if (strcmp(user_input, MY_COMMANDS[i]) == 0)
//         {
//             ;
//         }
//     }
// }

void handle_input(char *user_input)
{
    char *args[MAX_ARGS];
    get_args(user_input, args);

    // int is_system_command = system_command_exec(user_input);

    int fork_return = fork();
    if (fork_return)
    {
        wait(NULL);
    }
    else
    {
        // printf("%s", user_input);
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