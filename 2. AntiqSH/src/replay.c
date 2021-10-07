#include "all.h"
#include "my_command.h"
#include "misc.h"

/*
handles the replay command.
*/
void handle_replay(char *args[MAX_ARGS])
{
    char cmd[MAX_INPUT_LENGTH];
    int interval = 0;
    int period = 0;

    int i = 0;
    int j = 0;
    while (args[i])
    {
        if (args[i][0] == '-')
        {
            if (!args[i][1])
            {
                printf("Useless minus mmm\n");
                return;
            }

            if (!strcmp(args[i], "-interval"))
            {

                if (!args[i + 1])
                {
                    printf("no interval specified. bye\n");
                    return;
                }

                interval = atoi(args[i + 1]);
                if (!(interval <= INTERVAL_MAX && interval >= INTERVAL_MIN))
                {
                    printf("Naa, not allowed. get back in the range\n");
                    return;
                }
            }
            else if (!strcmp(args[i], "-period"))
            {

                if (!args[i + 1])
                {
                    printf("no period specified. bye\n");
                    return;
                }

                period = atoi(args[i + 1]);
                if (!(period <= PERIOD_MAX && period >= PERIOD_MIN))
                {
                    printf("Naa, not allowed. get back in the range\n");
                    return;
                }
            }
            else if (!strcmp(args[i], "-command"))
            {

                if (!args[i + 1])
                {
                    printf("no commands specified. bye\n");
                    return;
                }

                // start setting up the cmd
                strcpy(cmd, "");
                while (args[i + j + 1] && args[i + j + 1][0] != '-')
                {
                    strcat(cmd, args[i + j + 1]);
                    strcat(cmd, " ");
                    j++;
                }
            }
        }
        i++;
    }

    // printing cmd
    // printf("cmd: %s\n", cmd);

    char *cmd_args[MAX_ARGS];
    get_args(cmd, cmd_args);

    if (!interval || !period)
    {
        printf("unspecified interval or period\n");
        return;
    }

    int count = period / interval;
    while (1)
    {
        handle_command(0, cmd_args);

        if (--count <= 0)
            break;
        // fflush(stdout);
        sleep(interval);
    }
    return;
}
