#include "all.h"

/*
prints the process information
*/
void handle_pinfo(char *args[MAX_ARGS])
{
    // setup
    pid_t pid;
    char status[2];
    long memory;
    char exe_file_path[MAX_PATH_LEN] = "";
    char dummy[MAX_PATH_LEN];

    // FIND PID
    if (args[1]) // if supplied, use func from repeat.c
        pid = get_count(args[1]);
    else // else, get the current pid
        pid = getpid();
    printf("pid -- %ld\n", pid);

    pid_t pgroup = getpgid(pid);
    pid_t tgroup = tcgetpgrp(STDOUT_FILENO);
    char fgbg = (pgroup == tgroup) ? '+' : ' ';

    // FIND THE REST
    char status_file_name[MAX_PATH_LEN];
    char statm_file_name[MAX_PATH_LEN];
    char exe_file_name[MAX_PATH_LEN];

    sprintf(status_file_name, "/proc/%ld/stat", pid);
    sprintf(statm_file_name, "/proc/%ld/statm", pid);
    sprintf(exe_file_name, "/proc/%ld/exe", pid);

    // opening all the files
    FILE *status_file, *statm_file, *exe_file;
    status_file = fopen(status_file_name, "r");
    statm_file = fopen(statm_file_name, "r");

    if (!status_file)
    {
        printf("Process: %ld may not exist. Yeet.\n", pid);
        return;
    }

    fscanf(status_file, "%d %s %c", &pid, dummy, status);
    printf("Process Status -- %s%c\n", status, fgbg);

    fscanf(statm_file, "%ld", &memory);
    printf("memory -- %ld {Virual Memory}\n", memory);

    // closing all the files
    fclose(status_file);
    fclose(statm_file);

    int readlink_return = readlink(exe_file_name, exe_file_path, sizeof(exe_file_path));
    if (readlink_return == -1)
        printf("executable error");
    else
    {
        // compresses the path
        compress_path(exe_file_path, exe_file_path);
        printf("Executable Path -- %s\n", exe_file_path);
    }

    return;
}