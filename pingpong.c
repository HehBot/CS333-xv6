#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

#define BUFSIZE 512

int isalpha(char p)
{
    return (p >= 'a' && p <= 'z') || (p >= 'A' && p <= 'Z');
}

void ping_pong(int fd)
{
    char buf[BUFSIZE];
    int n, inword = 0, word_start = -1;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < n; i++) {
            if (!isalpha(buf[i])) {
                inword = 0;
                buf[i] = '\0';
                if (word_start != -1 && !strcmp(&buf[word_start], "ping"))
                    printf(1, "pong\n");
                word_start = -1;
                inword = 0;
            } else if (!inword) {
                inword = 1;
                word_start = i;
            }
        }
    }
    if (n < 0) {
        printf(1, "pingpong: read error\n");
        exit();
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf(1, "Usage: %s <input_file>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }

    ping_pong(fd);
    close(fd);

    exit();
}
