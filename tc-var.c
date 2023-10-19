#include "fcntl.h"
#include "stat.h"
#include "types.h"
#include "user.h"

int VAR = 0;

void increment(int* thread_rank)
{
    int tmp = VAR;
    sleep(10);
    tmp++;
    sleep(10);
    VAR = tmp;
    exit();
}

int main(int argc, char* argv[])
{

    int N = 20;
    printf(1, "Calling Process Print VAR value: %d, N: %d\n", VAR, N);

    for (int i = 0; i < N; i++) {
        create_thread(increment, &i);
    }

    for (int i = 0; i < N; i++) {
        join();
    }

    printf(1, "All threads joined, VAR value: %d\n", VAR);
    exit();
}
