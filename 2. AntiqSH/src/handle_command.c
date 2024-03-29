#include "all.h"
#include "proc.h"
#include "misc.h"

/*
handles my own written commands
input: ALL args
return 1 if I had a command for this shit, else nah
*/

extern struct proc
{
    int index;
    pid_t pid;
    char name[MAX_PROC_NAME];
} proc;

extern struct proc procs[MAX_PROCS];

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
            add_proc(pid, args[0]); // only saves the command name, not the args
            printf("pid: %ld, name: %s\n", pid, args[0]);
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

            if (WIFSTOPPED(wstatus))
            {
                // printf("pid: %ld, name: %s has been stopped\n", pid, args[0]);
                add_proc(pid, args[0]);
            }
        }
    }
    else if (pid == 0) //child
    {
        signal(SIGINT, SIG_DFL);  // restore ctrl+c
        signal(SIGTSTP, SIG_DFL); // restore ctrl+z

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
