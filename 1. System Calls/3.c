#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

/*
RESOURCES:
file and set permissions
https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c

printing
unistd.h https://en.wikipedia.org/wiki/Unistd.h
https://stackoverflow.com/questions/3866217/how-can-i-make-the-system-call-write-print-to-the-screen
*/

int main(int argc, char *argv[])
{
    char *input_file_name = argv[1];

    // set names
    char output_file1_name[128] = "Assignment/1_";
    strcat(output_file1_name, input_file_name);

    char output_file2_name[128] = "Assignment/2_";
    strcat(output_file2_name, input_file_name);

    char *output_file_names[] = {"Assignment", output_file1_name, output_file2_name};
    // done

    // loop through all of the names
    for (int i = 0; i < 3; i++)
    {
        // gets the satus of all the files
        struct stat fileStat;
        if (stat(output_file_names[i], &fileStat) < 0)
            return 1;

        // only prints this once
        if (!i)
        {
            char msg[128] = "Directory is created: ";
            strcat(msg, (S_ISDIR(fileStat.st_mode)) ? "Yes" : "No");
            strcat(msg, "\n\n");
            syscall(SYS_write, STDOUT_FILENO, msg, 128);
        }

        // printf("User has read permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IRUSR) ? "Yes" : "No");
        // printf("User has write permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IWUSR) ? "Yes" : "No");
        // printf("User has execute permission on %s: %s\n\n", output_file_names[i], (fileStat.st_mode & S_IXUSR) ? "Yes" : "No");
        // printf("Group has read permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IRGRP) ? "Yes" : "No");
        // printf("Group has write permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IWGRP) ? "Yes" : "No");
        // printf("Group has execute permission on %s: %s\n\n", output_file_names[i], (fileStat.st_mode & S_IXGRP) ? "Yes" : "No");
        // printf("Others has read permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IROTH) ? "Yes" : "No");
        // printf("Others has write permission on %s: %s\n", output_file_names[i], (fileStat.st_mode & S_IWOTH) ? "Yes" : "No");
        // printf("Others has execute permission on %s: %s\n\n", output_file_names[i], (fileStat.st_mode & S_IXOTH) ? "Yes" : "No");

        char msg1[128] = "User has read permission on ";
        strcat(msg1, output_file_names[i]);
        strcat(msg1, (fileStat.st_mode & S_IRUSR) ? ": Yes" : ": No");
        strcat(msg1, "\n");
        syscall(SYS_write, STDOUT_FILENO, msg1, 128);

        char msg2[128] = "User has write permission on ";
        strcat(msg2, output_file_names[i]);
        strcat(msg2, (fileStat.st_mode & S_IWUSR) ? ": Yes" : ": No");
        strcat(msg2, "\n");
        syscall(SYS_write, STDOUT_FILENO, msg2, 128);

        char msg3[128] = "User has execute permission on ";
        strcat(msg3, output_file_names[i]);
        strcat(msg3, (fileStat.st_mode & S_IXUSR) ? ": Yes" : ": No");
        strcat(msg3, "\n\n");
        syscall(SYS_write, STDOUT_FILENO, msg3, 128);

        char msg4[128] = "Group has read permission on ";
        strcat(msg4, output_file_names[i]);
        strcat(msg4, (fileStat.st_mode & S_IRGRP) ? ": Yes" : ": No");
        strcat(msg4, "\n");
        syscall(SYS_write, STDOUT_FILENO, msg4, 128);

        char msg5[128] = "Group has write permission on ";
        strcat(msg5, output_file_names[i]);
        strcat(msg5, (fileStat.st_mode & S_IWGRP) ? ": Yes" : ": No");
        strcat(msg5, "\n");
        syscall(SYS_write, STDOUT_FILENO, msg5, 128);

        char msg6[128] = "Group has execute permission on ";
        strcat(msg6, output_file_names[i]);
        strcat(msg6, (fileStat.st_mode & S_IXGRP) ? ": Yes" : ": No");
        strcat(msg6, "\n\n");
        syscall(SYS_write, STDOUT_FILENO, msg6, 128);

        char msg7[128] = "Others has read permission on ";
        strcat(msg7, output_file_names[i]);
        strcat(msg7, (fileStat.st_mode & S_IROTH) ? ": Yes" : ": No");
        strcat(msg7, "\n");
        syscall(SYS_write, STDOUT_FILENO, msg7, 128);

        char msg8[128] = "Others has write permission on ";
        strcat(msg8, output_file_names[i]);
        strcat(msg8, (fileStat.st_mode & S_IWOTH) ? ": Yes" : ": No");
        strcat(msg8, "\n");
        syscall(SYS_write, STDOUT_FILENO, msg8, 128);

        char msg9[128] = "Others has execute permission on ";
        strcat(msg9, output_file_names[i]);
        strcat(msg9, (fileStat.st_mode & S_IXOTH) ? ": Yes" : ": No");
        strcat(msg9, "\n\n");
        syscall(SYS_write, STDOUT_FILENO, msg9, 128);
    }

    return 0;
}