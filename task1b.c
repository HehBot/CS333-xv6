#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

char buff[512];
char addr[12];
int main(int argc, char* argv[])
{
    int fd;
    if (argc != 2) {
        printf(1, "Usage : %s <input_file>\n", argv[0]);
        exit();
    }
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }
    int offset = 1;
    int data_block_num = getdatablock(fd, offset); // to check task 1 systemcall 2
    if (data_block_num != -1)
        printf(1, "OFFSET %d is stored on DATABLOCK-%d on disk\n", offset, data_block_num);
    else
        printf(1, "given offset %d is > file size\n", offset);

    offset = 511;
    data_block_num = getdatablock(fd, offset); // to check task 1 systemcall 2
    if (data_block_num != -1)
        printf(1, "OFFSET %d is stored on DATABLOCK-%d on disk\n", offset, data_block_num);
    else
        printf(1, "given offset %d is > file size\n", offset);

    offset = 512;
    data_block_num = getdatablock(fd, offset); // to check task 1 systemcall 2
    if (data_block_num != -1)
        printf(1, "OFFSET %d is stored on DATABLOCK-%d on disk\n", offset, data_block_num);
    else
        printf(1, "given offset %d is > file size\n", offset);

    offset = 5000;
    data_block_num = getdatablock(fd, offset); // to check task 1 systemcall 2
    if (data_block_num != -1)
        printf(1, "OFFSET %d is stored on DATABLOCK-%d on disk\n", offset, data_block_num);
    else
        printf(1, "given offset %d is > file size\n", offset);

    offset = 9000;
    data_block_num = getdatablock(fd, offset); // to check task 1 systemcall 2
    if (data_block_num != -1)
        printf(1, "OFFSET %d is stored on DATABLOCK-%d on disk\n", offset, data_block_num);
    else
        printf(1, "given offset %d is > file size\n", offset);

    exit();
    return 0;
}
