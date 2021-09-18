#include "all.h"

/*
handles the echo command.
puts out all the stuff separated by " " only
*/
void handle_echo(char *args[MAX_ARGS])
{
    char full_string[MAX_ECHO_LEN] = "";
    int i = 1;
    while (args[i])
    {
        strcat(full_string, args[i]);
        strcat(full_string, " ");
        i++;
    }
    printf("%s\n", full_string);
    return;
}
