#include "commands.h"
#include "all.h"

using namespace std;

string test()
{
    return "testing 123!\n";
}

string handle_insert(char *args[MAX_ARGS])
{
    if (!(args[0] && args[1] && args[2]))
        return "Invalid #args\n";

    int key = atoi(args[1]);
    if (!(0 <= key && key <= 100))
        return "Invalid key\n";
    string value = args[2];

    if (dict[key].length())
        return "Key already exists\n";

    pthread_mutex_lock(&my_dict_mutex[key]);
    dict[key] = value;
    pthread_mutex_unlock(&my_dict_mutex[key]);

    return "Insertion Successful\n";
}

string handle_fetch(char *args[MAX_ARGS])
{
    if (!(args[0] && args[1]))
        return "Invalid #args\n";

    int key = atoi(args[1]);
    if (!(0 <= key && key <= 100))
        return "Invalid key\n";

    if (!dict[key].length())
        return "Key does not exist\n";
    else
        return dict[key];
}

string handle_delete(char *args[MAX_ARGS])
{
    if (!(args[0] && args[1]))
        return "Invalid #args\n";

    int key = atoi(args[1]);
    if (!(0 <= key && key <= 100))
        return "Invalid key\n";

    if (!dict[key].length())
        return "No such key exists\n";

    pthread_mutex_lock(&my_dict_mutex[key]);
    dict[key] = "";
    pthread_mutex_unlock(&my_dict_mutex[key]);
    return "Deletion successful\n";
}

string handle_update(char *args[MAX_ARGS])
{
    if (!(args[0] && args[1] && args[2]))
        return "Invalid #args\n";

    int key = atoi(args[1]);
    if (!(0 <= key && key <= 100))
        return "Invalid key\n";
    string value = args[2];

    if (!dict[key].length())
        return "Key dones not exist\n";

    pthread_mutex_lock(&my_dict_mutex[key]);
    dict[key] = value;
    pthread_mutex_unlock(&my_dict_mutex[key]);

    return "Updated value: " + value + "\n";
}

string handle_concat(char *args[MAX_ARGS])
{
    if (!(args[0] && args[1] && args[2]))
        return "Invalid #args\n";

    int key1 = atoi(args[1]);
    if (!(0 <= key1 && key1 <= 100))
        return "Invalid key1\n";
    int key2 = atoi(args[2]);
    if (!(0 <= key2 && key2 <= 100))
        return "Invalid key2\n";

    string temp1 = dict[key1];
    string temp2 = dict[key2];

    if (!(temp1.length() and temp2.length()))
        return "Concat failed as at least one of the keys does not exist\n";

    pthread_mutex_lock(&my_dict_mutex[key1]);
    pthread_mutex_lock(&my_dict_mutex[key2]);
    dict[key1] = temp1 + temp2;
    dict[key2] = temp2 + temp1;
    pthread_mutex_unlock(&my_dict_mutex[key2]);
    pthread_mutex_unlock(&my_dict_mutex[key1]);

    return "Concat value: " + dict[key2] + "\n";
}

string handle_commands(char *user_input)
{
    // cout << user_input << '\n';

    int i = 0;
    char **args = (char **)malloc(MAX_ARGS * sizeof(char *));

    args[i] = strtok(user_input, " \t");
    while (args[i])
        args[++i] = strtok(NULL, " \t");

    // for (int j = 0; j < i; j++)
    //     cout << "args: " << args[j] << '\n';

    string response = "\n";
    if (!strncmp(args[0], "test", 4))
        response = test();
    else if (!strncmp(args[0], "insert", 7))
        response = handle_insert(args);
    else if (!strncmp(args[0], "fetch", 6))
        response = handle_fetch(args);
    else if (!strncmp(args[0], "delete", 6))
        response = handle_delete(args);
    else if (!strncmp(args[0], "update", 6))
        response = handle_update(args);
    else if (!strncmp(args[0], "concat", 6))
        response = handle_concat(args);

    return response;
}
