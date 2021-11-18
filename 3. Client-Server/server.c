#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 1337
#define BUFFER_SIZE 256

int main()
{
    int sockfd, newsockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    // setup socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("cant open sock");
        exit(1);
    }
    // setup reuse address option for socket
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        perror("can't reuse addresses. sad.");
        exit(1);
    }

    // server addr struct setup
    bzero((char *)&server_addr, sizeof(server_addr)); // for resetting server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // bind the socket fd with server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("binding error");
        exit(1);
    }

    listen(sockfd, 5); // 5 is the max recommended size of the backlog queue
    client_len = sizeof(client_addr);

    while (1)
    {
        // accept connection request from client
        newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);

        if (newsockfd < 0)
        {
            perror("cant accept :pensive:");
            exit(1);
        }

        int bytes;
        bzero(buffer, BUFFER_SIZE);
        bytes = read(newsockfd, buffer, BUFFER_SIZE - 1);
        if (bytes < 0)
        {
            perror("cant read from sock ;-;");
            exit(1);
        }

        printf("Here is the message: %s\n", buffer);
        bytes = write(newsockfd, "I got your message.\n", 20);
        if (bytes < 0)
        {
            perror("y u dont listen client :/");
            exit(1);
        }

        close(newsockfd);
    }
    close(sockfd);
    return 0;
}
