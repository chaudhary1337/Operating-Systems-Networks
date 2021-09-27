#include "all.h"
#include "my_command.h"
#include "misc.h"

// DO SORTING AND JOB HANDLING WITH -r -s FLAGS

extern struct proc
{
    int index;
    pid_t pid;
    char name[MAX_PROC_NAME];
} proc;

extern struct proc procs[MAX_PROCS];

int cmp(const void *p1, const void *p2)
{
    struct proc *proc1 = (struct proc *)p1;
    struct proc *proc2 = (struct proc *)p2;
    return strcmp(proc1->name, proc2->name);
}

void handle_jobs(char *args[MAX_ARGS])
{
    for (int i = 0; i < MAX_PROCS; i++)
    {
        if (procs[i].pid)
        {
            char stat = get_status(procs[i].pid);
            char status[20];

            if (stat == 'T')
                strcpy(status, "Stopped");
            else
                strcpy(status, "Running");

            printf("[%d] %s %s [%ld]\n", procs[i].index, status, procs[i].name, procs[i].pid);
        }
    }
}
