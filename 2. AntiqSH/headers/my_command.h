#ifndef _MY_COMMAND_
#define _MY_COMMAND_

#include "all.h"

void handle_cd(char *args[MAX_ARGS]);
void handle_echo(char *args[MAX_ARGS]);
void handle_ls(char *args[MAX_ARGS]);
void handle_pwd();
void handle_repeat(int bg, char *args[MAX_ARGS]);
void handle_pinfo(char *args[MAX_ARGS]);

#endif
