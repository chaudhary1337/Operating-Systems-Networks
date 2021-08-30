#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
/*
RESOURCES:
https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
"fseek works with file pointers and lseek with file descriptors."  https://www.tek-tips.com/viewthread.cfm?qid=422167

*/

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
    // I/O SETUP
    char *input_path = argv[1];
    char *input_name = strrchr(input_path, '/') ? strrchr(input_path, '/') + 1 : input_path;
    int mkdir_result = mkdir("./Assignment/", 0700);
    char output_name[128] = "Assignment/2_";
    strcat(output_name, input_name);

    int input_file = open(input_path, O_RDONLY);
    int output_file = open(output_name, O_CREAT | O_RDWR | O_TRUNC, 0600);

    struct stat st;
    stat(input_path, &st);
    long int file_size = st.st_size;

    if (input_file < 0 || output_file < 0 || file_size < 0)
    {
        return 0;
    }

    // SETTING UP MORE STUFF
    int progress = 0;
    int chunk_size = get_int(argv[2]);
    int num_chunks = file_size / chunk_size + 1;
    int ans_chunk = get_int(argv[3]);
    int remainder = file_size - (num_chunks - 1) * chunk_size;
    lseek(input_file, (ans_chunk - 1) * chunk_size, SEEK_SET);
    chunk_size = ans_chunk < num_chunks ? chunk_size : remainder;

    char *source = (char *)malloc(chunk_size);
    char *target = (char *)malloc(chunk_size);

    read(input_file, source, chunk_size);
    for (int start = 0, end = chunk_size - 1; start < chunk_size; start++, end--)
    {
        target[start] = source[end];
        progress++;
        // sleep(1);
    }
    target[chunk_size] = '\0';
    write(output_file, target, chunk_size);
    char msg[8] = "";
    sprintf(msg, "\r%.2f%%", (float)progress / chunk_size * 100);
    syscall(SYS_write, STDOUT_FILENO, msg, 8);

    // COMPLETING STUFF
    close(input_file);
    close(output_file);
    return 0;
}