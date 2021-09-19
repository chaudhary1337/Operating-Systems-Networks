#include "all.h"

struct proc
{
    pid_t pid;
    char name[MAX_PROC_NAME];
};

struct proc procs[MAX_PROCS];

int get_how_many_procs()
{
    int count = 0;
    for (int i = 0; i < MAX_PROCS; i++)
        if (procs[i].pid)
            count++;
    return count;
}

void get_proc_name(pid_t proc_pid, char *proc_name)
{
    for (int i = 0; i < MAX_PROCS; i++)
    {
        if (procs[i].pid == proc_pid)
        {
            strcpy(proc_name, procs[i].name);
            return;
        }
    }
    return;
}

void add_proc(pid_t pid, char proc_name[MAX_PROC_NAME])
{
    for (int i = 0; i < MAX_PROCS; i++)
    {
        if (!procs[i].pid)
        {
            procs[i].pid = pid;
            strcpy(procs[i].name, proc_name);
            return;
        }
    }

    printf("No more space for procs :0 can't be saved.\n");
    return;
}

void remove_proc(pid_t pid)
{
    for (int i = 0; i < MAX_PROCS; i++)
    {
        if (procs[i].pid == pid)
        {
            procs[i].pid = 0;
            strcpy(procs[i].name, "");
            return;
        }
    }

    printf("If the proc isnt there, how can I remove it >.<\n");
}

void print_procs()
{
    printf("********************************************************************************\n");
    int count = 0;
    for (int i = 0; i < MAX_PROCS; i++)
    {
        if (procs[i].pid)
        {
            printf("process with pid: %ld, name: %s is active.\n", procs[i].pid, procs[i].name);
        }
    }
    printf("********************************************************************************\n");
    return count;
}
