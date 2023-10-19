#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

struct barrier {
    int sem_protect;
    int sem_release1;
    int sem_release2;
    int num_threads;
    int count;
};

struct barrier bar;

void barrier_init(struct barrier* bar, int num_threads)
{
    bar->sem_protect = semaphore_init(1);
    bar->sem_release1 = semaphore_init(0);
    bar->sem_release2 = semaphore_init(0);
    bar->num_threads = num_threads;
    bar->count = 0;
}

void barrier_place(struct barrier* bar)
{
    semaphore_down(bar->sem_protect);
    bar->count++;
    if (bar->count == bar->num_threads) {
        for (int i = 0; i < bar->num_threads; ++i)
            semaphore_up(bar->sem_release1);
    }
    semaphore_up(bar->sem_protect);
    semaphore_down(bar->sem_release1);

    semaphore_down(bar->sem_protect);
    bar->count--;
    if (bar->count == 0) {
        for (int i = 0; i < bar->num_threads; ++i)
            semaphore_up(bar->sem_release2);
    }
    semaphore_up(bar->sem_protect);
    semaphore_down(bar->sem_release2);
}

void work(int* thread_num)
{
    for (int i = 0; i < 3; i++) {
        barrier_place(&bar);
        printf(1, "LOOP %d | Section 1 of code | Thread Number: %d\n", i, *thread_num);
        barrier_place(&bar);
        printf(1, "LOOP %d | Section 2 of code | Thread Number: %d\n", i, *thread_num);
    }
    exit();
}

int main(int argc, char* argv[])
{
    int N = 5;
    barrier_init(&bar, N);
    int ind[N];
    for (int i = 0; i < N; i++) {
        ind[i] = i;
        create_thread(work, &ind[i]);
    }
    for (int i = 0; i < N; i++)
        join();

    printf(1, "All threads joined, code completed\n");
    exit();
}
