#ifndef _ALL_
#define _ALL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <bits/stdc++.h>
#include <sys/types.h>

#define PORT 1337
#define BUFFER_SIZE 256
#define MAX_DICT_SIZE 101
#define MAX_STRING_SIZE 256
#define BACKLOG 5
#define MAX_RESPONSE_SIZE 256
#define MAX_REQUESTS 256

using namespace std;

extern vector<string> dict;
extern pthread_mutex_t my_dict_mutex[MAX_DICT_SIZE];

#endif
