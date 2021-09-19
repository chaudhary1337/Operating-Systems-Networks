#include "all.h"

typedef void info_handler(int, siginfo_t *, void *);

extern struct proc
{
    pid_t pid;
    char name[MAX_PROC_NAME];
};

extern struct proc procs[MAX_PROCS];

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

        if (!strcmp(child_name, ""))
            continue;

        if (WIFEXITED(wstatus))
            fprintf(stderr, "\nchild %s with pid: %ld exited normally/abnormally :D\n", child_name, child_pid);
        else
            fprintf(stderr, "\nsomething went wrong with child with pid: %d. 0xFFFFF.\n", child_pid);

        remove_proc(child_pid); // remove the process from the list
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
