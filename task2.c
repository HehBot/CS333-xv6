#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

#define BUFFSIZE 95
char buff[BUFFSIZE + 1];
char addr[BUFFSIZE + 1];

int main(int argc, char* argv[])
{
    int fd;

    if (argc != 2) {
        printf(1, "Usage : %s <input_file>\n", argv[0]);
        exit();
    }

    fd = open(argv[1], O_CREATE | O_ENCRYPT);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    // char buff[]="hello this message needs to be encrypted and contents should not be visible,pingpong.txt Hello this is the first occurence of ping. You must have used ping command in Linux. A process could use the ping system call to check network connectivity.\0";
    char buff[] = "you are looking at confidential text\nThis text is not supposed to be visible on raw block reads\n";
    write(fd, buff, BUFFSIZE);
    close(fd);

    fd = open(argv[1], O_ENCRYPT);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    int offset;
    offset = 1;
    int db = getdatablock(fd, offset);
    readdatablock(1, (char*)addr, db);
    addr[BUFFSIZE] = '\0';
    printf(1, "%s\n", addr);
    close(fd);

    fd = open(argv[1], O_ENCRYPT);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    read(fd, addr, BUFFSIZE);
    addr[BUFFSIZE] = '\0';
    printf(1, "%s\n", addr);
    close(fd);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    read(fd, addr, BUFFSIZE);
    addr[BUFFSIZE] = '\0';
    printf(1, "%s\n", addr);
    close(fd);

    exit();
}
