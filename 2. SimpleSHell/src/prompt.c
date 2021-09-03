#include "all.h"

// handle path later on!

void show_prompt()
{
    char host_name[HOST_NAME_MAX + 1];
    gethostname(host_name, sizeof(host_name));

    printf("<%s@%s>", getenv("USER"), host_name);

    return;
}
