#include "stat.h"
#include "types.h"
#include "user.h"

int main(int argc, char* argv[])
{
    if (argc <= 1) {

        printf(1, "Enter number of processes to fork:\n");
        exit();
    }

    int initial_time = uptime();

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {

        if (fork() == 0) {
            int a = 1;
            a += 1;

            int* counter = (int*)(smalloc());
            int* counter2 = (int*)(smalloc());
            *counter = 56;
            printf(1, "PID: %d, VA: %x, Counter Value: %d\n", getpid(), counter, *counter);
            printf(1, "PID: %d, VA: %x, Counter2 Value: %d\n", getpid(), counter2, *counter2);
            exit();
        }
    }

    int* final = (int*)(smalloc());

    for (int i = 0; i < n; i++) {

        wait();
    }

    printf(1, "PID: %d, VA: %x, Final Count: %d\n", getpid(), final, *final);
    int final_time = uptime();

    printf(1, "Total Ticks Taken: %d\n", final_time - initial_time);
    exit();
}
