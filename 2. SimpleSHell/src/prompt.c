#include "all.h"

char home[256];

void get_path(char *ans_path)
{
    char *curr_path = getenv("PWD");

    // only first time, save the current path in home.
    if (!strlen(home))
    {
        strcpy(home, curr_path);
    }

    char final_path[256];
    if (strcmp(home, curr_path) == 0)
    {
        strcpy(final_path, "~");
    }
    // LOGIC TO BE DONE AFTER CD IS IMPLEMENTED
    else if (strlen(home) > strlen(curr_path))
    {
        strcpy(final_path, "bigger string to be fixed after cd is implmented");
    }
    else
    {
        strcpy(final_path, "smaller string to be fixed after cd is implemented");
    }

    strcpy(ans_path, final_path);
    return;
}

void show_prompt()
{
    char host_name[HOST_NAME_MAX + 1];
    gethostname(host_name, sizeof(host_name));

    char final_path[256];
    get_path(final_path);
    printf("<%s@%s:%s>", getenv("USER"), host_name, final_path);

    return;
}
