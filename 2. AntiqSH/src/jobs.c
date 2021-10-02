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
    int running = 0;
    int stopped = 0;
    int i = 0;
    while (args[i])
    {
        if (args[i][0] == '-') // flag
        {
            int j = 1;
            while (args[i][j])
            {
                if (args[i][j] == 'r')
                    running = 1;
                else if (args[i][j] == 's')
                    stopped = 1;
                else
                {
                    printf("only -r and -s allowed brrr\n");
                    return;
                }

                j++;
            }

            if (j == 1)
            {
                printf("supply the args after flag. duh.\n");
                return;
            }
        }
        i++;
    }

    // if no args supplied, set both to 1
    if (!running && !stopped)
        running = stopped = 1;

    // sort with the help of the cmp comparator function
    qsort(procs, get_how_many_procs(), sizeof(struct proc), cmp);

    // iterate over the procs and do stuff
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

            if ((status[0] == 'S' && stopped) || (status[0] == 'R' && running))
                printf("[%d] %s %s [%ld]\n", i, status, procs[i].name, procs[i].pid);
        }
    }
}
