#include "all.h"

typedef void info_handler(int, siginfo_t *, void *);

info_handler *install_signal(int signum, info_handler *handler)
{
    struct sigaction action, old_action;

    memset(&action, 0, sizeof(struct sigaction));
    action.sa_sigaction = handler;
    sigemptyset(&action.sa_mask);              /* block sigs of type being handled */
    action.sa_flags = SA_RESTART | SA_SIGINFO; /* restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0)
        perror("antiqsh");
    return (old_action.sa_sigaction);
}

void handle_child(int sig, siginfo_t *info, void *vp)
{
    return;
}

void start_child_handler()
{
    install_signal(SIGCHLD, handle_child);
    return;
}
