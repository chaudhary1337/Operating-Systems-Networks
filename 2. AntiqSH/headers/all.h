#ifndef _ALL_
#define _ALL_

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_ARGS 16
#define MAX_FILES 4
#define MAX_PATH_LEN 256
#define MAX_ECHO_LEN 256
#define BUFFER_SIZE 4096
#define MAX_INPUT_LENGTH 256
#define MAX_PROC_NAME 256
#define MAX_PROCS 256
#define MAX_TIME 64
#define INTERVAL_MAX 10
#define PERIOD_MAX 10
#define INTERVAL_MIN 1
#define PERIOD_MIN 1
#define MAX_REPLAY_CMD 4

#endif
