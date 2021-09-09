#include "all.h"

int main()
{
    char *user_input = NULL;
    size_t size = 1;

    while (1)
    {
        show_prompt();
        int bytes_input = getline(&user_input, &size, stdin);

        if (bytes_input == -1)
        {
            puts("\nAdios!");
            break;
        }
        else
        {
            handle_input(user_input);
        }
    }
    free(user_input);
    return 0;
}
