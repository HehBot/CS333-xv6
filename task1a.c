#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

char buff[512];
char addr[12];
int main(int argc, char* argv[])
{
    int fd;

    fd = open("small.txt", O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    int inum = getinodenum(fd); // to check task 1 systemcall 1
    printf(1, "inode number of fd-%d is %d\n", fd, inum);

    fd = open("medium.txt", O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    inum = getinodenum(fd);
    printf(1, "inode number of fd-%d is %d\n", fd, inum);

    fd = open("big.txt", O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    inum = getinodenum(fd);
    printf(1, "inode number of fd-%d is %d\n", fd, inum);

    exit();
    return 0;
}
