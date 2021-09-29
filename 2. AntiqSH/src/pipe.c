#include "all.h"
#include "misc.h"
#include "my_command.h"

void handle_pipe(char *segments[MAX_INPUT_LENGTH], int i)
{
    int old_fds[2];
    int new_fds[2];

    // handle each segment as if it were a command
    for (int j = 0; j < i; j++)
    {
        if (j + 1 < i)
        {
            if (pipe(new_fds) < 0)
            {
                printf("pipe error. call mario!\n");
                return;
            }
        }
        pid_t pid = fork();
        if (pid < 0)
        {
            printf("fork error in pipe. sOmBaDy ToUch mY SphAgEt");
            return;
        }
        else if (pid > 0) // parent
        {
            // wait(NULL);
            if (j > 0)
            {
                close(old_fds[0]);
                close(old_fds[1]);
            }
            if (j + 1 < i)
            {
                // replacing old with new
                // if next command present
                old_fds[0] = new_fds[0];
                old_fds[1] = new_fds[1];
            }
        }
        else //child
        {
            if (j > 0)
            {
                dup2(old_fds[0], 0);
                close(old_fds[0]);
                close(old_fds[1]);
            }
            if (j + 1 < i)
            {
                close(new_fds[0]);
                dup2(new_fds[1], 1);
                close(new_fds[1]);
            }

            char *args[MAX_ARGS];
            get_args(segments[j], args);
            int exec_return = execvp(args[0], args);
            if (exec_return < 0) // if invalid command, print its invalid and exit
            {
                printf("Command \"%s\" not found.\n", args[0]);
                exit(0);
            }
        }
    }

    return;
}
