#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/*
RESOURCES:
https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c
*/

int main(int argc, char *argv[])
{
    char *input_file_name = argv[1];

    // set names
    char output_file1_name[128] = "Assignment/1_";
    strcat(output_file1_name, input_file_name);

    char output_file2_name[128] = "Assignment/2_";
    strcat(output_file2_name, input_file_name);
    // done

    char *output_file_names[] = {"Assignment", output_file1_name, output_file2_name};

    for (int i = 0; i < 3; i++)
    {
        // gets the satus of all the files
        struct stat fileStat;
        if (stat(output_file_names[i], &fileStat) < 0)
        {
            return 1;
        }

        // only prints this once
        if (!i)
        {
            printf("Directory is created: %s\n\n", (S_ISDIR(fileStat.st_mode)) ? "Yes" : "No");
        }

        printf("User has read permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IRUSR) ? "Yes" : "No");
        printf("User has write permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IWUSR) ? "Yes" : "No");
        printf("User has execute permission on %s: %s\n\n", output_file_names[i], (fileStat.st_mode & S_IXUSR) ? "Yes" : "No");
        printf("Group has read permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IRGRP) ? "Yes" : "No");
        printf("Group has write permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IWGRP) ? "Yes" : "No");
        printf("Group has execute permission on %s: %s\n\n", output_file_names[i], (fileStat.st_mode & S_IXGRP) ? "Yes" : "No");
        printf("Others has read permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IROTH) ? "Yes" : "No");
        printf("Others has write permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IWOTH) ? "Yes" : "No");
        printf("Others has execute permission on %s: %s\n\n", output_file_names[i], (fileStat.st_mode & S_IXOTH) ? "Yes" : "No");
    }

    return 0;
}