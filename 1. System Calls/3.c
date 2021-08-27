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
    char *input_path = argv[1];
    char *input_file_name = strrchr(input_path, '/') ? strrchr(input_path, '/') + 1 : input_path;

    // set names
    char output_file1_path[128] = "./Assignment/1_";
    char output_file1_name[128] = "1_";
    strcat(output_file1_path, input_file_name);
    strcat(output_file1_name, input_file_name);

    char output_file2_path[128] = "./Assignment/2_";
    char output_file2_name[128] = "2_";
    strcat(output_file2_path, input_file_name);
    strcat(output_file2_name, input_file_name);

    char *output_file_paths[] = {"Assignment", output_file1_path, output_file2_path};
    char *output_file_names[] = {"Assignment", output_file1_name, output_file2_name};
    // done

    char *owner[] = {"User", "Group", "Others"};
    char *ops[] = {"read", "write", "execute"};
    int flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    for (int file = 0; file < 3; file++)
    {
        struct stat fileStat;
        int result = stat(output_file_paths[file], &fileStat);

        // only when file is 0, that is, the directory
        if (!file)
        {
            char dirmsg[128] = "Directory is created: ";
            strcat(dirmsg, (S_ISDIR(fileStat.st_mode)) ? "Yes" : "No");
            strcat(dirmsg, "\n\n");
            syscall(SYS_write, STDOUT_FILENO, dirmsg, 128);
        }

        // gets the satus of all the files
        if (result < 0)
        {
            char errmsg[128] = "Error accessing the file/dir: ";
            strcat(errmsg, output_file_paths[file]);
            strcat(errmsg, "\n\n");
            syscall(SYS_write, STDOUT_FILENO, errmsg, 128);
            continue;
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                char msg[128] = "";
                strcat(msg, owner[i]);
                strcat(msg, " has ");
                strcat(msg, ops[j]);
                strcat(msg, " permission on ");
                strcat(msg, output_file_names[file]);
                strcat(msg, ": ");
                strcat(msg, (fileStat.st_mode & flags[3 * i + j]) ? "Yes" : "No");
                strcat(msg, "\n");
                syscall(SYS_write, STDOUT_FILENO, msg, 128);
            }
            syscall(SYS_write, STDOUT_FILENO, "\n", 1);
        }
    }

    return 0;
}
