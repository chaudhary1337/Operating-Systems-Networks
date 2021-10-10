#include "all.h"
#include "my_command.h"
#include "misc.h"

int handle_wait()
{
    fd_set fds;
    struct timeval tv;
    int retval;

    FD_ZERO(&fds);
    FD_SET(0, &fds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    retval = select(1, &fds, NULL, NULL, &tv);
    if (retval == -1)
    {
        printf("select didnt return shit.\n");
        return 1;
    }
    else if (retval)
    {
        if (fgetc(stdin) == 'q')
            return 1;
    }

    return 0;
}

void handle_newborn(int interval)
{
    char dummy[4][MAX_PATH_LEN];
    pid_t pid;
    char *file_name = "/proc/loadavg";
    FILE *file = fopen(file_name, "r");

    if (!file)
    {
        printf("error in opening loadavg.\n", pid);
        return;
    }

    while (1)
    {
        fscanf(file, "%s%s%s%s %d", dummy[0], dummy[1], dummy[2], dummy[3], &pid);
        printf("proc: %d\n", pid);
        fflush(stdout);
        sleep(interval);

        if (handle_wait())
            break;
    }

    fclose(file);
}

void handle_interrupt(int interval)
{
    char dummy[4][MAX_PATH_LEN];
    pid_t pid;
    char *file_name = "/proc/interrupts";
    FILE *file = fopen(file_name, "r");

    if (!file)
    {
        printf("error in opening interrupt.\n", pid);
        return;
    }

    char line[MAX_INPUT_LENGTH];
    fgets(line, MAX_INPUT_LENGTH, file);
    printf("%s\n", line);
    while (1)
    {
        // skip over the first 3 lines the next time
        FILE *file = fopen(file_name, "r");
        for (int i = 0; i < 3; i++)
            fgets(line, MAX_INPUT_LENGTH, file);
        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == ':')
            {
                for (int x = 0; x <= i; x++)
                    line[x] = ' ';
            }

            if (line[i] == 'I')
            {
                line[i] = '\0';
                break;
            }
        }
        printf("%s\n", line);

        sleep(interval);
        if (handle_wait())
            break;
    }

    fclose(file);
}

void handle_baywatch(char *args[MAX_ARGS])
{
    int interval = 0;
    int i = 0;
    int interrupt = 0;
    int newborn = 0;
    while (args[i])
    {
        if (args[i][0] == '-')
        {
            if (!args[i][1])
            {
                printf("Useless minus mmm\n");
                return;
            }

            if (!strcmp(args[i], "-n"))
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
        }
        else
        {
            if (!strcmp(args[i], "newborn"))
            {
                newborn = 1;
            }
            else if (!strcmp(args[i], "interrupt"))
            {
                interrupt = 1;
            }
        }
        i++;
    }

    if (!interval)
    {
        printf("interval not specified\n");
        return;
    }

    if (!newborn && !interrupt)
        printf("? nothing to do??\n");
    else if (newborn)
        handle_newborn(interval);
    else if (interrupt)
        handle_interrupt(interval);

    return;
}