#include "all.h"

/*
yet to handle errors
input: array of characters
output: int of the count they are
*/
int get_count(char *num)
{
    int ans = 0;
    while (*num)
    {
        ans = ans * 10 + *num - '0';
        num++;
    }
    return ans;
}

void handle_repeat(char *args[MAX_ARGS])
{
    // printf("in repeat\n");
    int count = get_count(args[1]);
    // printf("count %d\n", count);

    char *new_args[MAX_ARGS];
    int i = 2;
    while (args[i])
    {
        new_args[i - 2] = args[i];
        // printf("got: %s\n", new_args[i - 2]);
        i++;
    }

    // i = 0;
    // while (new_args[i])
    //     printf("again: %s\n", new_args[i++]);

    while (count--)
    {
        // printf("handling commands ...\n");
        handle_command(new_args);
    }
}