#include "all.h"
#include "misc.h"
#include "my_command.h"

/*
handle io stuff: ONLY piping for now
*/
void handle_io(char *user_input)
{
    // each segment has been split by its pipes
    // since that is the highest priority operation
    char *segments[MAX_INPUT_LENGTH];
    int i = 0;
    segments[i] = strtok(user_input, "|");
    while (segments[i])
        segments[++i] = strtok(NULL, "|");

    handle_pipe(segments, i);

    return;
}
