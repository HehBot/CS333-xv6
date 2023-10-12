#include "date.h"
#include "defs.h"
#include "memlayout.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"
#include "types.h"
#include "x86.h"

int sys_fork(void)
{
    return fork();
}

int sys_exit(void)
{
    exit();
    return 0; // not reached
}

int sys_wait(void)
{
    return wait();
}

int sys_kill(void)
{
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    return kill(pid);
}

int sys_getpid(void)
{
    return myproc()->pid;
}

int sys_sbrk(void)
{
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

int sys_sleep(void)
{
    int n;
    uint ticks0;

    if (argint(0, &n) < 0)
        return -1;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (myproc()->killed) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

int sys_cscount(void)
{
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    struct proc* p = myproc();
    cprintf("pid [%d] switch in [%d],switch out [%d]\n", p->pid, p->switch_in, p->switch_out);
    return 0;
}

int sys_wait2(void)
{
    int* wtime;
    int* runtime;

    if (argint(0, (void*)&wtime) < 0 || argint(1, (void*)&runtime) < 0)
        return -1;

    return wait2(wtime, runtime);
}

int sys_set_priority(void)
{
    int pid, priority;

    if (argint(0, &pid) < 0 || argint(1, &priority) < 0)
        return -1;

    return set_priority(pid, priority);
}

int sys_set_quanta(void)
{
    int pid, quanta;

    if (argint(0, &pid) < 0 || argint(1, &quanta) < 0)
        return -1;

    return set_quanta(pid, quanta);
}
