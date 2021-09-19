#include "all.h"

/*
handles my own written commands
input: ALL args
return 1 if I had a command for this shit, else nah
*/

extern struct proc
{
    pid_t pid;
    char name[MAX_PROC_NAME];
};

extern struct proc procs[MAX_PROCS];

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
    else if (!strncmp(args[0], "ls", 2))
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
    if (pid < 0) // fork error
    {
        perror("antqish");
    }
    else if (pid > 0) // parent
    {
        if (bg)
        {
            add_proc(pid, args[0]);
            printf("pid: %ld, ppid: %ld, name: %s\n", pid, (long)getpid(), args[0]);
        }
        else
        {
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(STDIN_FILENO, pid);
            int wstatus;
            waitpid(-1, &wstatus, WUNTRACED);
            tcsetpgrp(STDIN_FILENO, getpgrp());

            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
    }
    else if (pid == 0) //child
    {
        setpgid(0, 0);
        int exec_return = execvp(args[0], args);
        if (exec_return < 0) // if invalid command, print its invalid and exit
        {
            printf("Command \"%s\" not found.\n", args[0]);
            exit(0);
        }
    }
    return;
}
