#include "all.h"
#include "misc.h"

char all_modes[10];

void get_permission(char *file)
{
    struct stat fileStat;
    if (!stat(file, &fileStat))
    {
        all_modes[0] = S_ISDIR(fileStat.st_mode) ? 'd' : '-';
        int flags[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
        char ops[3] = {'r', 'w', 'x'};

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                all_modes[1 + 3 * i + j] = (fileStat.st_mode & flags[3 * i + j]) ? ops[j] : '-';
        all_modes[10] = '\0';
    }
}

void listed_show(char *file_address, char *file)
{
    struct stat data;
    if (stat(file_address, &data) == -1)
    {
        printf("something wrong happened mmm :thonk:\n");
        return;
    }
    struct group *curr_group = getgrgid(data.st_gid);
    struct passwd *curr_password = getpwuid(data.st_uid);
    char time[MAX_TIME];
    strftime(time, MAX_TIME, "%b  %d %H:%M", localtime(&data.st_mtime));
    printf("%s\t%ld\t%s\t%s\t", all_modes, data.st_nlink, curr_password->pw_name, curr_group->gr_name);
    printf("%ld\t %s\t%s\n", data.st_size, time, file);
}

void ls_list(char *dir_address, int list, int hidden)
{
    struct dirent *file;
    DIR *dir = opendir(dir_address);
    // the ta Mehu Goel cut marks for this lmao
    // if (list)
    //     printf("directory/file: %s\n", dir_address);
    struct stat data;
    if (stat(dir_address, &data) == -1)
    {
        printf("something wrong happened for the dir/file :thonk:\n");
        return;
    }

    if (S_ISDIR(data.st_mode) && dir)
    {
        if (list)
            printf("%d\n", (int)data.st_blksize);

        while ((file = readdir(dir)))
        {
            if (!hidden && (file->d_name[0] == '.'))
                continue;

            char file_address[MAX_PATH_LEN];
            strcpy(file_address, dir_address);
            strcat(file_address, "/");
            strcat(file_address, file->d_name);
            get_permission(file_address);

            if (!list)
                printf("%s\n", file->d_name);
            else
                listed_show(file_address, file->d_name);
        }
        closedir(dir);
    }
    else if (!S_ISDIR(data.st_mode))
    {
        char *dir_address_name = strrchr(dir_address, '/') ? strrchr(dir_address, '/') + 1 : dir_address;

        if (list)
            listed_show(dir_address, dir_address_name);
        else
            printf("%s\n", dir_address_name);
    }
    else
    {
        printf("Not valid directory; check perms or name :/\n");
        return;
    }
}

void handle_ls(char *args[MAX_ARGS])
{
    // gets the args
    int i = 1, hidden = 0, list = 0;
    char file_names[MAX_FILES][MAX_PATH_LEN] = {};
    int file_name_ptr = 0;
    while (args[i])
    {
        if (args[i][0] == '-') // flag
        {
            int j = 1;
            while (args[i][j])
            {
                if (args[i][j] == 'a')
                    hidden = 1;
                else if (args[i][j] == 'l')
                    list = 1;
                else
                {
                    printf("only -a and -l allowed brrr\n");
                    return;
                }

                j++;
            }

            if (j == 1)
            {
                printf("supply the args after flag. duh.\n");
                return;
            }
        }
        else // file names
        {
            strcpy(file_names[file_name_ptr], args[i]);
            file_name_ptr++;
        }
        i++;
    }

    // if none specified, do for the current dir
    if (!file_name_ptr)
        getcwd(file_names[0], sizeof(file_names[0]));
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (!strcmp(file_names[i], ""))
            continue;

        if (!strcmp(file_names[i], "~"))
        {
            char temp[MAX_PATH_LEN];
            expand_path(file_names[i], temp);
            strcpy(file_names[i], temp);
            // printf("TEMP: %s\n", temp);
        }
        // printf("'%s'\n", file_names[i]);
        i++;
    }

    for (int i = 0; i < MAX_FILES; i++)
    {
        if (!strcmp(file_names[i], ""))
            break;
        ls_list(file_names[i], list, hidden);
        puts("\n");
    }

    return;
}
