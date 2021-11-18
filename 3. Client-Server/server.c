#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 1337
#define BUFFER_SIZE 256
#define MAX_DICT_SIZE 100
#define MAX_STRING_SIZE 256

char dict[MAX_DICT_SIZE][MAX_STRING_SIZE];

void check(int code, char message[MAX_STRING_SIZE])
{
    if (code < 0)
    {
        printf("%s\n", message);
        exit(1);
    }
    return;
}

void handle_connection(int client_socket)
{
    // steup buffer
    char buffer[BUFFER_SIZE];
    int bytes;
    bzero(buffer, BUFFER_SIZE);

    // read data from client
    check(read(client_socket, buffer, BUFFER_SIZE - 1), "cant read from sock ;-;");

    // print data from client
    printf("Here is the message: %s\n", buffer);

    // write ack to client
    check(write(client_socket, "I got your message.\n", 20), "y u dont listen client :/");

    // close connection
    close(client_socket);
}

int main(int argc, char *argv[])
{
    // handle args
    if (argc != 2)
    {
        printf("need one param to specify #clients threads");
        exit(1);
    }
    int num_clients = atoi(argv[1]);

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
    // 5 is the max recommended size of the backlog queue
    check(listen(sockfd, 5), "cant listen :/");

    while (1)
    {
        // accept connection request from client
        check(client_socket = accept(sockfd, (struct sockaddr *)&client_addr, &client_len), "can't accept :pensive:");

        // handle connection from client
        handle_connection(client_socket);
    }

    // close server socket
    close(sockfd);
    return 0;
}
