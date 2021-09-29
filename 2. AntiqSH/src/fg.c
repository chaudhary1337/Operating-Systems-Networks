#include "all.h"
#include "my_command.h"
#include "misc.h"

extern struct proc
{
    int index;
    pid_t pid;
    char name[MAX_PROC_NAME];
} proc;

extern struct proc procs[MAX_PROCS];

void handle_fg(char *args[MAX_ARGS])
{
    // #args
    if (!args[1])
    {
        printf("specify the proc index dammit.\n");
        return;
    }

    // get the index
    int index = atoi(args[1]);
    if (index < 0 || index >= MAX_PROCS)
    {
        printf("I only want index, no id or str or sm grabage.\n");
        return;
    }

    if (!procs[index].pid)
    {
        printf("that proc doesn't exist or youre too late\n");
        return;
    }

    // handle the continuation
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

    tcsetpgrp(STDIN_FILENO, procs[index].pid);
    kill(procs[index].pid, SIGCONT); // continue the proc
    int wstatus;
    waitpid(-1, &wstatus, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    if (!WIFSTOPPED(wstatus)) // if it aint stopped, it gon
    {
        // removing the proc from bg
        procs[index].index = -1;
        procs[index].pid = 0;
        strcpy(procs[index].name, "");
    }
}
