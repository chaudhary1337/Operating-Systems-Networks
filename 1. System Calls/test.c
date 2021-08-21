#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

int get_int(char *num)
{
    int ans = 0;

    while (*num)
    {
        ans = ans * 10 + *num - '0';
        num++;
    }

    return ans;
}

int main(int argc, char *argv[])
{
    int x = get_int(argv[2]);
    printf("%d", x);
    return 0;
}