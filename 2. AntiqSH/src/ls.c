#include "all.h"

void handle_ls(char *args[MAX_ARGS])
{
    int i = 0;
    while (args[i])
    {
        printf("%s\n", args[i]);
        i++;
    }
    return;
}
