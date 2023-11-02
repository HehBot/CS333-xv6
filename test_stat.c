#include "stat.h"
#include "user.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf(1, "usage:  %s <filenames...>\n", argv[0]);
        exit();
    }

    struct stat s;
    for (int i = 1; i < argc; ++i) {
        if (stat(argv[i], &s) < 0)
            printf(1, "error: file %s not found\n", argv[i]);
        else {
            printf(1, "\
File: %s\n\
     Size: %d bytes\n\
     Type: %d (%s)\n\
     Device: %d\n\
     Inode number: %d\n\
     Links or References: %d\n\
",
                   argv[i], s.size, s.type, (s.type == T_DIR ? "T_DIR" : s.type == T_FILE ? "T_FILE"
                                                                                          : "T_DEV"),
                   s.dev, s.ino, s.nlink);
        }
    }
    exit();
}
