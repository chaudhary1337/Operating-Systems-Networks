#include "all.h"

/*
first parameter is the user input
goal: stores the arguments in the second input parameter as a list of strings
*/
void get_args(char *user_input, char *args[MAX_ARGS])
{
    int i = 0;
    args[i] = strtok(user_input, " ");
    while (args[i])
    {
        args[++i] = strtok(NULL, " ");
    }
}

/*
returns 1 if current command is bg
*/
int is_bg(char *user_input)
{
    //if is bg, we remove the & character, end the string there
    // and return 1
    for (int i = 0; i < strlen(user_input); i++)
    {
        if (user_input[i] == '&')
        {
            user_input[i] = '\0';
            return 1;
        }
    }

    // if no & found, lite
    return 0;
}

/*
called by the main function to handle the user input
sends the parsed arguments over to handle_command()
*/
void handle_input(char *user_input)
{
    char *args[MAX_ARGS];
    int bg = is_bg(user_input);
    get_args(user_input, args);
    handle_command(bg, args);
    return;
}
