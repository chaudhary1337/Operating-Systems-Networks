#include "all.h"

char *MY_COMMANDS[] = {"wow"};

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
    // last was a '\n' and i don't like that
    user_input[strlen(user_input) - 1] = '\0';

    system(user_input);

    // int is_system_command = system_command_exec(user_input);

    // int fork_return = fork();
    // if (fork_return)
    // {
    //     wait(NULL);
    // }
    // else
    // {
    //     // printf("%s", user_input);
    //     int exec_return = system(user_input);
    //     // if invalid command, print its invalid and exit
    //     if (exec_return < 0)
    //     {
    //         printf("Command \"%s\" not found!\n", user_input);
    //         exit(0);
    //     }
    // }
    return;
}