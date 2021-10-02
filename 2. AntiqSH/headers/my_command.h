#ifndef _MY_COMMAND_
#define _MY_COMMAND_

#include "all.h"
#include "proc.h"

void handle_cd(char *args[MAX_ARGS]);
void handle_echo(char *args[MAX_ARGS]);
void handle_ls(char *args[MAX_ARGS]);
void handle_pwd();
void handle_repeat(int bg, char *args[MAX_ARGS]);
void handle_pinfo(char *args[MAX_ARGS]);
void handle_jobs(char *args[MAX_ARGS]);
void handle_fg(char *args[MAX_ARGS]);
void handle_bg(char *args[MAX_ARGS]);
void handle_sig(char *args[MAX_ARGS]);
void handle_pipe(char *segments[MAX_INPUT_LENGTH], int i);
void handle_redirect(char *segment);
int handle_input_redirect(char *args[MAX_ARGS]);
int handle_output_redirect(char *args[MAX_ARGS]);

#endif
