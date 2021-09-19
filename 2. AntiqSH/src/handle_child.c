#include "all.h"

typedef void info_handler(int, siginfo_t *, void *);

struct proc
{
    pid_t pid;
    char name[MAX_PROC_NAME];
};

struct proc procs[MAX_PROCS];
int proc_counter = 0;

// installs signal. ez.
info_handler *install_signal(int signum, info_handler *handler)
{
    struct sigaction action, old_action;

    memset(&action, 0, sizeof(struct sigaction));
    action.sa_sigaction = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART | SA_SIGINFO;

    if (sigaction(signum, &action, &old_action) < 0)
        perror("antiqsh");
    return (old_action.sa_sigaction);
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

    printf("Can't find the process name :(\n");
    return;
}

/*
called whenever SIGCHLD signal is sent
yeets processes who were going to become zombies
*/
void handle_child(int sig, siginfo_t *info, void *ucontext)
{
    int wstatus;
    pid_t child_pid;
    while ((child_pid = waitpid(-1, &wstatus, WNOHANG)) > 0)
    {
        char child_name[MAX_PROC_NAME] = "";
        get_proc_name(child_pid, child_name);
        if (WIFEXITED(wstatus))
            printf("\nchild %s with pid: %ld exited :D\n", child_name, child_pid);
        else
            printf("\nsomething went wrong with child with pid: %d. 0xFFFFF.\n", child_pid);

        // also reduce the process counter
        proc_counter--;
    }

    return;
}

// preps to handle children before they become zombies
// installs the SIGCHLD signal to handle the termination of children
void start_child_handler()
{
    install_signal(SIGCHLD, handle_child);
    return;
}
