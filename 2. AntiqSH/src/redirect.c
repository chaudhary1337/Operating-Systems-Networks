#include "all.h"
#include "misc.h"
#include "my_command.h"

void handle_input_redirect(char *args[MAX_ARGS])
{
    // dup2(STDIN_FD, STDIN_FILENO);
    // dup2(STDOUT_FD, STDOUT_FILENO);
    // close(STDIN_FD);
    // close(STDOUT_FD);

    // puts("hi");
    int i = 0;
    while (args[i])
    {
        // printf("=== args man %s ===\n", args[i]);
        if (!strcmp(args[i], "<"))
        {
            // printf("=== wtf man %s ===\n", args[i]);

            if (i == 0)
            {
                printf("who do i feed this input to, huh?\n");
                return;
            }
            if (!args[i + 1])
            {
                printf("where input??\n");
                return;
            }

            // open the file
            int fd_in = open(args[i + 1], O_RDONLY);
            if (fd_in < 0)
            {
                printf("some error in opening file :hmmm:\n");
                return;
            }

            dup2(fd_in, STDIN_FILENO); // send the data to file
            close(fd_in);

            // shift the args by 2
            while (args[i])
                args[i] = args[i + 2];

            // if found one redirect, yeeettt
            break;
        }
        i++;
    }
    return;
}

void handle_redirect(char *segment)
{
    char *args[MAX_ARGS];
    get_args(segment, args);
    handle_input_redirect(args);

    // int x = 0;
    // while (args[x])
    //     printf("args in redir: %s\n", args[x++]);

    int exec_return = execvp(args[0], args);
    if (exec_return < 0) // if invalid command, print its invalid and exit
    {
        printf("Command \"%s\" not found.\n", args[0]);
        exit(0);
    }
    return;
}
