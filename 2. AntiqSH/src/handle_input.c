#include "all.h"
#include "misc.h"

/*
first parameter is the SPLITTED user input
goal: stores the arguments in the second input parameter as a list of strings
*/
void get_args(char *user_input, char *args[MAX_ARGS])
{
    int i = 0;
    args[i] = strtok(user_input, " \t");
    while (args[i])
        args[++i] = strtok(NULL, " \t");
}

/*
returns 1 if the supplied user_input has i/o stuff, else 0
*/
int is_io(char *user_input)
{
    // if is bg, we remove the & character, end the current user_input there
    // and return 1
    for (int i = 0; i < strlen(user_input); i++)
        if (user_input[i] == '<' || user_input[i] == '>' || user_input[i] == '|')
            return 1;

    // if no i/o character found, lite
    return 0;
}

/*
returns 1 if the supplied user_input is bg else 0
*/
int is_bg(char *user_input)
{
    // if is bg, we remove the & character, end the current user_input there
    // and return 1
    for (int i = 0; i < strlen(user_input); i++)
    {
        if (user_input[i] == '&')
        {
            user_input[i] = '\0';
            return 1;
        }
    }

    // if no '&' found, lite
    return 0;
}

/*
input: user_input, raw
output: nothing

called by the main function to handle the user input
- splits the string by ; into multiple user_inputs
- gets info on if they are bg or not
- gets all the args for a particular user_input
- sends the parsed arguments over to handle_command()
*/
void handle_input(char *user_input)
{
    char *user_inputs[MAX_INPUT_LENGTH];
    int i = 0;
    user_inputs[i] = strtok(user_input, ";");
    while (user_inputs[i])
        user_inputs[++i] = strtok(NULL, ";");

    for (int j = 0; j < i; j++)
    {
        // for each input, separated by ;
        char user_input[MAX_INPUT_LENGTH];
        strcpy(user_input, user_inputs[j]);

        if (is_io(user_input)) // i/o command goes through a diff route
        {
            handle_io(user_input);
        }
        else // non-io commands handle as before
        {
            int bg = is_bg(user_input);
            char *args[MAX_ARGS];
            get_args(user_input, args);
            handle_command(bg, args);
        }
    }
    return;
}
