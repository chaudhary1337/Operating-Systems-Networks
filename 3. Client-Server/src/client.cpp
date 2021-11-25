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

void handle_connect(string input)
{
    int sockfd;
    struct sockaddr_in server_addr;
    char rbuff[BUFFER_SIZE];

    check((sockfd = socket(AF_INET, SOCK_STREAM, 0)), "cant create sock\n");

    bzero((char *)&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    check(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)), "cant connect to server\n");
    send(sockfd, input.c_str(), strlen(input.c_str()), 0);
    check(recv(sockfd, rbuff, BUFFER_SIZE, 0) - 1, "can't recevie\n");
    fputs(rbuff, stdout);
    bzero((char *)&rbuff, sizeof(rbuff));

    close(sockfd);
}

int main()
{
    ///////////////////////////// HANDLING ALL THE INPUTS /////////////////////
    string temp;
    getline(cin, temp);
    int m = stoi(temp);
    int last_time = 0;
    vector<vector<string>> inputs(MAX_REQUESTS);
    for (int i = 0; i < m; i++)
    {
        string temp;
        getline(cin, temp);
        string time = temp.substr(0, temp.find(' '));
        string remaining = temp.substr(temp.find(' ') + 1, temp.length() - 1);

        inputs[stoi(time)].push_back(remaining);
        last_time = max(last_time, stoi(time));
    }
    ///////////////////////////// HANDLING ALL THE INPUTS /////////////////////

    for (int i = 1; i <= last_time; i++)
    {
        for (int j = 0; j < inputs[i].size(); j++)
            handle_connect(inputs[i][j]);
        sleep(1);
    }

    return 0;
}
