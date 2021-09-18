#include "all.h"

int main()
{
    // prep to handle SIGCHLD
    start_child_handler();

    char *user_input = NULL;
    size_t size = 1;

    while (1)
    {
        // shows the prompt. duh.
        show_prompt();

        // taking user input
        int bytes_input = getline(&user_input, &size, stdin);
        if (bytes_input == -1) // if Ctrl+D, Adios!
        {
            puts("\nAdios!");
            break;
        }
        else
        {
            // last was a '\n' and i dont like that
            user_input[strlen(user_input) - 1] = '\0';
            // if user_input is something,
            // then ...
            // do something dammit
            if (strlen(user_input))
                handle_input(user_input);
        }
    }

    return 0;
}
