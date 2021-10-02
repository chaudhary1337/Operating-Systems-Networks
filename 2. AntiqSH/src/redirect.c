#include "all.h"
#include "misc.h"
#include "my_command.h"

int handle_input_redirect(char *args[MAX_ARGS])
{
    int i = 0;
    while (args[i])
    {
        if (!strcmp(args[i], "<"))
        {
            if (i == 0)
            {
                printf("who do i feed this input to, huh?\n");
                return 1;
            }
            if (!args[i + 1])
            {
                printf("where input??\n");
                return 1;
            }

            // open the file
            int fd_in = open(args[i + 1], O_RDONLY);
            if (fd_in < 0)
            {
                printf("some error in opening file :hmmm:\n");
                return 1;
            }

            dup2(fd_in, STDIN_FILENO); // send the data to file
            close(fd_in);

            // shift the args by 2
            while (args[i])
            {
                args[i] = args[i + 2];
                i++;
            }

            // if found one redirect, yeeettt
            // int x = 0;
            // while (args[x])
            //     printf("args in redir: %s\n", args[x++]);
            break;
        }
        i++;
    }
    return 0;
}

int handle_output_redirect(char *args[MAX_ARGS])
{
    int i = 0;
    while (args[i])
    {
        if (!strcmp(args[i], ">") || !strcmp(args[i], ">>"))
        {

            if (i == 0)
            {
                printf("where do I get this output from, huh?\n");
                return 1;
            }
            if (!args[i + 1])
            {
                printf("where output??\n");
                return 1;
            }

            // open the file
            int fd_out;
            if (!strcmp(args[i], ">"))
                fd_out = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                fd_out = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd_out < 0)
            {
                printf("some error in opening file :hmmm:\n");
                return 1;
            }

            dup2(fd_out, STDOUT_FILENO); // send the data to file
            close(fd_out);

            // // shift the args by 2
            // while (args[i])
            // {
            //     args[i] = args[i + 2];
            //     i++;
            // }

            // if found one redirect, yeeettt
            break;
        }
        i++;
    }
    return 0;
}

void handle_redirect(char *segment)
{
    char *args[MAX_ARGS];
    get_args(segment, args);
    int input_redirect_return = handle_input_redirect(args);
    if (input_redirect_return)
    {
        exit(0);
        return;
    }
    int output_redirect_return = handle_output_redirect(args);
    if (output_redirect_return)
    {
        exit(0);
        return;
    }

    int exec_return = execvp(args[0], args);
    if (exec_return < 0) // if invalid command, print its invalid and exit
    {
        printf("Command \"%s\" not found.\n", args[0]);
        exit(0);
    }
    return;
}
