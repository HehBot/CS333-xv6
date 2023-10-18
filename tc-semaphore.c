#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

int VAR = 0;
int sem;

void increment(int* thread_rank)
{
    semaphore_down(sem);
    int tmp = VAR;
    sleep(10);
    tmp++;
    sleep(10);
    VAR = tmp;
    semaphore_up(sem);
    exit();
}

int main(int argc, char* argv[])
{

    sem = semaphore_init(1);
    int N = 20;
    printf(1, "Calling Process Print VAR value: %d, N: %d\n", VAR, N);

    for (int i = 0; i < N; i++) {
        create_thread(increment, &i);
    }

    for (int i = 0; i < N; i++) {
        join();
    }

    printf(1, "All threads joined, VAR value: %d\n", VAR);
    semaphore_destroy(sem);
    exit();
}