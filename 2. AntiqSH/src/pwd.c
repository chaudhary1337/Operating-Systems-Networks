#include "all.h"

/*
prints the current absolute path
*/
void handle_pwd()
{
    char curr_path[MAX_PATH_LEN];
    getcwd(curr_path, sizeof(curr_path));
    printf("%s\n", curr_path);
    return;
}
