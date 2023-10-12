#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

int main(int argc, char* argv[])
{

    printf(1, "---------Testcase: context switch------Scheduler: DEFAULT-------------------------------------\n");

    for (int child = 1; child <= 3; child++) {
        int pid = fork();
        if (pid < 0) {
            printf(1, "%d failed in fork!\n", getpid());
            exit();
        } else if (pid == 0) {
            cscount(getpid());
            printf(1, "Child %d started\n", getpid());
            volatile double a, b;
            a = 3.14;
            b = 36.29;
            volatile double x = 0, z;
            for (z = 0; z < 9000000.0; z += 0.1) {
                x = x + a * b;
            }
            printf(1, "Child %d finished\n", getpid());
            cscount(getpid());
            exit();
        }
    }
    int reaped_pid;

    reaped_pid = wait();
    printf(1, "Child pid: %d exited\n", reaped_pid);

    reaped_pid = wait();
    printf(1, "Child pid: %d exited\n", reaped_pid);

    reaped_pid = wait();
    printf(1, "Child pid: %d exited\n", reaped_pid);

    exit();
}
