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

            int* counter = (int*)(smalloc());

            for (int j = 0; j < 10; j++) {

                acquiresleeplk();
                int temp = *counter;
                sleep(1);
                temp = temp + 1;
                *counter = temp;
                releasesleeplk();
            }

            exit();
        }
    }

    int* final = (int*)(smalloc());

    for (int i = 0; i < n; i++) {

        wait();
    }

    printf(1, "Actual Count: %d\n", *final);
    printf(1, "Expected Count: %d\n", n * 10);
    int final_time = uptime();

    printf(1, "Total Ticks Taken: %d\n", final_time - initial_time);
    exit();
}