#include "all.h"

using namespace std;

#define PORT 1337
#define BUFFER_SIZE 256
#define MAX_DICT_SIZE 100
#define MAX_STRING_SIZE 256
#define BACKLOG 5

// char dict[MAX_DICT_SIZE][MAX_STRING_SIZE];
vector<string> dict(MAX_DICT_SIZE, "");

queue<int *> q;
vector<pthread_t> thread_pool;
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t my_condition = PTHREAD_COND_INITIALIZER;

void check(int code, const char *message)
{
    if (code < 0)
    {
        printf("%s\n", message);
        exit(1);
    }
    return;
}

void *handle_connection(void *ptr_client_socket)
{
    int client_socket = *((int *)ptr_client_socket);

    // steup buffer
    char buffer[BUFFER_SIZE];
    int bytes;
    bzero(buffer, BUFFER_SIZE);

    // read data from client
    check(read(client_socket, buffer, BUFFER_SIZE - 1), "cant read from sock ;-;");
    buffer[BUFFER_SIZE - 1] = '\0'; // null terminating it, just in case

    // print data from client
    printf("Here is the message: %s\n", buffer);

    // write ack to client
    check(write(client_socket, "I got your message.\n", 20), "y u dont listen client :/");

    // close connection
    close(client_socket);

    return NULL;
}

void *handle_thread(void *arg)
{
    while (true)
    {
        int *client_socket = NULL;

        // PROTECC THE QUEUE OPERATIONS
        pthread_mutex_lock(&my_mutex);
        if (q.empty())
        {
            pthread_cond_wait(&my_condition, &my_mutex);
        }
        // NOT SURE IF I SHOULD JUST `else` OR PUT ANOTHER IF
        // WILL GO WITH ANOTHER IF, SINCE SAFER XD
        if (!q.empty())
        {
            client_socket = q.front(); //get the first element
            // cout << "pre yeet\n";
            q.pop(); // YEET
            // cout << q.size() << "\tpost yeet\n";
        }
        pthread_mutex_unlock(&my_mutex);

        // cout << "off to connection\n";
        if (client_socket)
            handle_connection(client_socket);
        // cout << "connection done\n";
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    //////////////////////// THREAD HANDLING //////////////////////////////////
    // handle args
    if (argc != 2)
    {
        printf("need one param to specify #client threads");
        exit(1);
    }
    int num_clients = atoi(argv[1]);
    thread_pool.resize(num_clients);
    for (int i = 0; i < num_clients; i++)
        pthread_create(&thread_pool[i], NULL, handle_thread, NULL);
    ///////////////////////////////////////////////////////////////////////////

    //////////////////////// SOCKET HANDLING //////////////////////////////////
    // setup data structures and shit
    int sockfd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    // setup socket
    check(sockfd = socket(AF_INET, SOCK_STREAM, 0), "cant open sock");
    // setup reuse address option for socket
    int enable = 1;
    check(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)), "cant reuse addrs");
    // server addr struct setup
    bzero((char *)&server_addr, sizeof(server_addr)); // for resetting server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    // bind the socket fd with server address
    check(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)), "cant bind :0");
    // listen!
    check(listen(sockfd, BACKLOG), "cant listen :/");
    ///////////////////////////////////////////////////////////////////////////
    // cout << "yo1" << '\n';

    while (true)
    {
        // accept connection request from client
        // cout << "yo2" << '\n';

        check(client_socket = accept(sockfd, (struct sockaddr *)&client_addr, &client_len), "can't accept :pensive:");

        // DUMB METHOD: handle connection from client
        // handle_connection(client_socket); // for one thread only

        // LESSER DUMB METHOD: A THREAD A CLIENT
        // pthread_t t;
        // pthread_create(&t, NULL, handle_connection, &client_socket);

        // NON-DUMB METHOD
        // cout << "yo3" << '\n';
        int *client_on_heap = (int *)malloc(sizeof(int));
        *client_on_heap = client_socket;

        pthread_mutex_lock(&my_mutex);
        q.push(client_on_heap);
        pthread_cond_signal(&my_condition);
        pthread_mutex_unlock(&my_mutex);
    }

    // close server socket
    close(sockfd);
    return 0;
}
