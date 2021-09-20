#ifndef _PROC_
#define _PROC_

#include "all.h"

int get_how_many_procs();
void get_proc_name(pid_t proc_pid, char *proc_name);
void add_proc(pid_t pid, char proc_name[MAX_PROC_NAME]);
void remove_proc(pid_t pid);
void print_procs();

#endif
