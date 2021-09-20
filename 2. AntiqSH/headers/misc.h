#ifndef _MISC_
#define _MISC_

#include "all.h"

// input
void get_args(char *user_input, char *args[MAX_ARGS]);
int is_bg(char *user_input);
void handle_input(char *user_input);

// commands
void handle_command(int bg, char *args[MAX_ARGS]);
int handle_my_command(int bg, char *args[MAX_ARGS]);

// child
typedef void info_handler(int, siginfo_t *, void *);
info_handler *install_signal(int signum, info_handler *handler);
void handle_child(int sig, siginfo_t *info, void *ucontext);
void start_child_handler();

// prompt
void get_path(char *ans_path, char *final_path_unmodded);
void show_prompt();

// path utils
void compress_path(char *path, char *compressed_path);
void expand_path(char *path, char *expanded_path);

#endif
