#include "all.h"

void handle_pwd(char *args[MAX_ARGS])
{
    char curr_path[256];
    getcwd(curr_path, sizeof(curr_path));
    printf("%s\n", curr_path);
    return;
}