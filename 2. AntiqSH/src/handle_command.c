#include "all.h"

/*
handles my own written commands
input: ALL args
return 1 if I had a command for this shit, else nah
*/
int handle_my_command(int bg, char *args[MAX_ARGS])
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
    else if (!strncmp(args[0], "pwd", 3))
    {
        handle_pwd();
        return 1;
    }
    else if (!strncmp(args[0], "echo", 4))
    {
        handle_echo(args);
        return 1;
    }
    else if (!strncmp(args[0], "repeat", 6))
    {
        handle_repeat(bg, args);
        return 1;
    }

    return 0;
}

/*
takes care of the arguments and tries to execute them 
input: args
returns: nothing
*/
void handle_command(int bg, char *args[MAX_ARGS])
{
    // handle my own implemented commands
    int is_my_command = handle_my_command(bg, args);
    if (is_my_command)
        return;

    // if I don't have it implemented, time to call execvp
    pid_t pid = fork();
    if (pid > 0) // parent
    {
        int wstatus;
        if (!bg)
        {
            // wait(NULL); is same as below, but clen
            waitpid(-1, &wstatus, 0);
        }
        else
        {
            printf("pid: %ld, ppid: %ld, name: %s\n", (long)getpid(), (long)getppid(), args[0]);
        }
    }
    else if (pid == 0)
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
    else // return < 0 for errors in forking
    {
        perror("antqish");
    }
    return;
}
