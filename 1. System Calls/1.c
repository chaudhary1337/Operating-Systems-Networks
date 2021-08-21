#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
RESOURCES:
https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
"fseek works with file pointers and lseek with file descriptors."  https://www.tek-tips.com/viewthread.cfm?qid=422167

*/

int main(int argc, char *argv[])
{
    // I/O SETUP
    char *input_name = argv[1];
    char output_name[128] = "Assignment/1_";
    strcat(output_name, input_name);

    int input_file = open(input_name, O_RDONLY);
    int output_file = open(output_name, O_CREAT | O_RDWR | O_TRUNC, 0600);

    struct stat st;
    stat(input_name, &st);
    long int file_size = st.st_size;

    if (input_file < 0 || output_file < 0 || file_size < 0)
    {
        exit(1);
    }

    // SETTING UP MORE STUFF
    int chunk_size = 4;
    int num_chunks = file_size / chunk_size + 1;

    // HANDLING THE REMAINDER FROM THE DIVISION
    int remaining = file_size - (num_chunks - 1) * chunk_size;
    lseek(input_file, -remaining, SEEK_END);

    char *source = (char *)malloc(remaining);
    char *target = (char *)malloc(remaining);

    read(input_file, source, remaining);
    for (int start = 0, end = remaining - 1; start < remaining; start++, end--)
        target[start] = source[end];
    write(output_file, target, remaining);

    // HANDLING CORE OF THE FILE
    source = (char *)malloc(chunk_size);
    target = (char *)malloc(chunk_size);
    int curr_chunk = num_chunks - 2; // pointing to the second last chunk

    // CHONKY BOIHS
    while (1)
    {
        lseek(input_file, curr_chunk-- * chunk_size, SEEK_SET);
        read(input_file, source, chunk_size);
        for (int start = 0, end = chunk_size - 1; start < chunk_size; start++, end--)
            target[start] = source[end];
        target[chunk_size] = '\0';
        write(output_file, target, chunk_size);

        if (curr_chunk < 0)
            break;
    }

    // COMPLETING STUFF
    close(input_file);
    close(output_file);
    return 0;
}