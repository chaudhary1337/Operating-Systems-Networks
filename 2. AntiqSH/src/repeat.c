#include "all.h"

/*
yet to handle errors
input: array of characters
output: int of the count they are
*/
int get_count(char *num)
{
    return atoi(num);
}

void handle_repeat(int bg, char *args[MAX_ARGS])
{
    // if no count given
    if (!args[1])
    {
        printf("Gimme the count ;-;\n");
        return;
    }
    // if the wrong count is given
    int count = get_count(args[1]);
    if (!(count > 0 && count <= 15))
    {
        printf("The count is too big or you screwed the count bruh.\n");
        return;
    }
    // if no command passed
    if (!args[2])
    {
        printf("Bhai repeat kya karu mein?? :pensive:\n");
        return;
    }
    // actual code now
    char *new_args[MAX_ARGS] = {};
    int i = 2;
    while (args[i])
    {
        new_args[i - 2] = args[i];
        i++;
    }

    while (count--)
        handle_command(bg, new_args);

    return;
}
