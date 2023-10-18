#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

struct barrier {
    // ******************************
    // WPTHREAD -- START
    // ******************************
    // ADD VARIABLES YOU MIGHT NEED HERE

    // ******************************
    // WPTHREAD -- END
    // ******************************
};

struct barrier bar;

void barrier_init(struct barrier* bar, int num_threads)
{
    // ******************************
    // WPTHREAD -- START
    // ******************************

    // ******************************
    // WPTHREAD -- END
    // ******************************
}

void barrier_place(struct barrier* bar)
{
    // ******************************
    // WPTHREAD -- START
    // ******************************

    // ******************************
    // WPTHREAD -- END
    // ******************************
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

    for (int i = 0; i < N; i++) {
        create_thread(work, &i);
    }

    for (int i = 0; i < N; i++) {
        join();
    }

    printf(1, "All threads joined, code completed\n");
    exit();
}