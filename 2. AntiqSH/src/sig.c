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

void handle_sig(char *args[MAX_ARGS])
{
    // #args
    if (!args[2])
    {
        printf("specify the proc index & SIG# dammit.\n");
        return;
    }

    // get the index & sig number
    int index = atoi(args[1]);
    int signal = atoi(args[2]);
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

    kill(procs[index].pid, signal);
    return;
}
