#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char msg[] = "wow very nice";
    strcat(msg, " hihihi");
    syscall(SYS_write, STDOUT_FILENO, msg, sizeof(msg));

    return 0;
}