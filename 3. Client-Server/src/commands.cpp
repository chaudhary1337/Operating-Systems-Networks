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

    while (!my_dict_mutex[key].try_lock())
        ;
    if (dict[key].length())
        return "Key already exist\n";
    dict[key] = value;
    my_dict_mutex[key].unlock();

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

    dict[key] = "";
    return "Deletion successful\n";
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
    // else if (!strncmp(args[0], "delete", 6))
    //     response = handle_delete(args);
    // else if (!strncmp(args[0], "update", 6))
    //     response = handle_update(args);
    // else if (!strncmp(args[0], "concat", 6))
    //     response = handle_concat(args);

    return response;
}
