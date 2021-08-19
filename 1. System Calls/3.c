#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *input_file_name = argv[1];

    char output_file1[128] = "1_";
    strcat(output_file1, input_file_name);

    char output_file2[128] = "2_";
    strcat(output_file2, input_file_name);

    // printf("%s\n", input_file_name);
    // printf("%s\n", output_file1);
    // printf("%s", output_file2);
    return 0;
}