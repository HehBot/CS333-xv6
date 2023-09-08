#include "stat.h"
#include "types.h"
#include "user.h"

#define EXTMEM 0x100000
#define KERNBASE 0x80000000 // First kernel virtual address
#define KERNLINK (KERNBASE + EXTMEM) // Address where kernel is linked

int main(int argc, char* argv[])
{
    int N = 10;
    int uva = (int)&N; // the virtual address of n
    int kva1 = (int)(KERNLINK + 1024);
    int kva2 = (int)(KERNLINK + 2048);
    int kva3 = (int)(KERNLINK + 4096);
    int kva4 = (int)(KERNLINK + 5192);

    printf(1, "Physical Address of user   virtual address %p is %p\n", uva, va2pa(uva));
    printf(1, "Physical Address of Kernel virtual address %p is %p\n", kva1, va2pa(kva1));
    printf(1, "Physical Address of Kernel virtual address %p is %p\n", kva2, va2pa(kva2));
    printf(1, "Physical Address of Kernel virtual address %p is %p\n", kva3, va2pa(kva3));
    printf(1, "Physical Address of Kernel virtual address %p is %p\n", kva4, va2pa(kva4));

    exit();
}
