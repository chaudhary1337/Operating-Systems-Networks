#include "all.h"
#include "misc.h"
#include "my_command.h"

void handle_pipe(char *segments[MAX_INPUT_LENGTH], int i)
{
    int new_pfd[2];
    int old_pfd[2] = {STDIN_FILENO, STDOUT_FILENO};
    int save_out = dup(STDOUT_FILENO);
    int save_in = dup(STDOUT_FILENO);

    // handle each segment as if it were a command
    for (int j = 0; j < i; j++)
    {
        int pipe_return = pipe(new_pfd);
        if (pipe_return < 0)
        {
            printf("pipe error. call mario!\n");
            return;
        }
        pid_t pid = fork();
        if (pid < 0)
        {
            printf("fork error in pipe. sOmBaDy ToUch mY SphAgEti");
            return;
        }
        else if (pid > 0) // parent
        {
            wait(NULL);
            close(new_pfd[1]);       // closing the write end of pipe
            old_pfd[0] = new_pfd[0]; // saving the old pipe
        }
        else //child
        {
            dup2(old_pfd[0], STDIN_FILENO); // reading from the pipe of last command.
            if (j + 1 != i)                 // if not the end, stdout to curr pipe
                dup2(new_pfd[1], STDOUT_FILENO);
            close(new_pfd[0]);

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

    dup2(save_in, STDIN_FILENO);
    dup2(save_out, STDOUT_FILENO);
    return;
}
