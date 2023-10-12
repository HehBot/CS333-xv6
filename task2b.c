#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

void computation(int quanta)
{
    int child_pid = getpid();
    // set_priority(child_pid, priority);

    printf(1, "Child [%d] created T.Q. [%d]\n", child_pid, quanta);
    volatile double a, b;
    a = 3.14;
    b = 36.29;
    volatile double x = 0, z;
    for (z = 0; z < 90000.0; z += 0.1) {
        x = x + a * b;
    }
    printf(1, "Child [%d] finished\n", getpid());
    exit();
}

int main(int argc, char* argv[])
{
    printf(1, "---------Testcase: set quanta------Scheduler: DEFAULT-------------------------------------\n");

    for (int child = 1; child <= 3; child++) {
        // int quanta = 10-child*3;
        int quanta = 1;
        if (child == 1)
            quanta = 8;
        if (child == 2)
            quanta = 4;
        if (child == 3)
            quanta = 2;

        int pid = fork();

        set_quanta(pid, quanta);

        if (pid < 0) {
            printf(1, "%d failed in fork!\n", getpid());
            exit();
        } else if (pid == 0) {
            // Child process: Execute the computation function with priority
            computation(quanta);
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
