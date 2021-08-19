#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

int main()
{
    char msg[] = "wow very nice";
    strcat(msg, " hihihi");
    syscall(SYS_write, STDOUT_FILENO, msg, sizeof(msg));

    char owner[] = {"User", "Group", "Others"};
    char ops[] = {"read", "write", "execute"};
    int flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    for (int i = 0; i < 3; i++)
    {
        char msg[128] = owner[i];
        for (int j = 0; j < 3; j++)
        {
            strcat(msg, " has ");
            strcat(msg, ops[j]);
            strcat(msg, " permission on {}:");
            strcat(msg, flags[3 * i + j]);
        }
    }

    return 0;
}