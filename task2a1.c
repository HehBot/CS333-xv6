
#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

void computation(int priority)
{
    int child_pid = getpid();

    printf(1, "Child %d created priority %d\n", child_pid, priority);
    volatile double a, b;
    a = 3.14;
    b = 36.29;
    volatile double x = 0, z;
    for (z = 0; z < 900000.0; z += 0.1) {
        x = x + a * b;
    }
    printf(1, "Child %d finished\n", getpid());
    exit();
}

int main(int argc, char* argv[])
{
    printf(1, "---------Testcase 1: set priority------Scheduler: PRIORITY BASED-------------------------------------\n");

    for (int child = 1; child <= 3; child++) {
        int priority = 4; // Calculate priority for each child

        int pid = fork();

        set_priority(pid, priority);

        if (pid < 0) {
            printf(1, "%d failed in fork!\n", getpid());
            exit();
        } else if (pid == 0) {
            // Child process: Execute the computation function with priority
            computation(priority);
        }
        // Parent continues creating more children
    }

    int wtime, rtime, status;

    for (int i = 1; i <= 3; i++) {
        status = wait2(&wtime, &rtime);
        printf(1, "Child pid: %d exited with pid: %d, Waiting Time: %d, Run Time: %d\n", status, status, wtime, rtime);
    }

    exit();
}
