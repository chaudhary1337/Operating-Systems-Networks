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

void handle_bg(char *args[MAX_ARGS])
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
        printf("that proc doesn't exist dumbass\n");
        return;
    }

    kill(procs[index].pid, SIGCONT);

    return;
}
