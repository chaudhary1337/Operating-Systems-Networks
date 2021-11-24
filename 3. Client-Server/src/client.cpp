#include "all.h"

void check(int code, const char *message)
{
    if (code < 0)
    {
        printf("%s\n", message);
        exit(1);
    }
    return;
}

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    string sbuff;
    char rbuff[BUFFER_SIZE];

    check((sockfd = socket(AF_INET, SOCK_STREAM, 0)), "cant create sock\n");

    bzero((char *)&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    check(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)), "cant connect to server\n");
    getline(cin, sbuff);
    send(sockfd, sbuff.c_str(), strlen(sbuff.c_str()), 0);
    check(recv(sockfd, rbuff, BUFFER_SIZE, 0) - 1, "can't recevie\n");
    fputs(rbuff, stdout);
    close(sockfd);

    return 0;
}
