#include "all.h"
#include "proc.h"

struct proc
{
    int index;
    pid_t pid;
    char name[MAX_PROC_NAME];
} proc;

struct proc procs[MAX_PROCS];

void init_procs()
{
    for (int i = 0; i < MAX_PROCS; i++)
    {
        procs[i].index = -1;
        procs[i].pid = 0;
        strcpy(procs[i].name, "");
    }
    return;
}

int get_how_many_procs()
{
    int count = 0;
    for (int i = 0; i < MAX_PROCS; i++)
        if (procs[i].pid)
            count++;
    return count;
}

char get_status(pid_t pid)
{
    // get status
    char status[20];
    char dummy[MAX_PATH_LEN];
    char status_file_name[MAX_PATH_LEN];
    sprintf(status_file_name, "/proc/%ld/stat", pid);

    FILE *status_file;
    status_file = fopen(status_file_name, "r");
    fscanf(status_file, "%d %s %s", &pid, dummy, status);
    fclose(status_file);
    return status[0];
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
            procs[i].index = i;
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
    for (int i = 0; i < MAX_PROCS; i++)
    {
        if (procs[i].pid)
        {
            printf("process with pid: %ld, name: %s is active.\n", procs[i].pid, procs[i].name);
        }
    }
    printf("********************************************************************************\n");
}
