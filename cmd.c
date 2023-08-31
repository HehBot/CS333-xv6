#include "user.h"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        printf(1, "Usage: %s <command>\n", argv[0]);
        exit();
    }

    int p = fork();
    if (p == 0) {
        char* args[64];
        for (int i = 1; i < argc; ++i)
            args[i - 1] = argv[i];
        args[argc - 1] = NULL;
        exec(args[0], args);
    } else
        wait();

    exit();
}
