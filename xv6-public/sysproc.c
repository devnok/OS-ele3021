#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

char PASSWORD[11] = "2019065650";

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int sys_getgpid(void) {
    struct proc *par = myproc();
    while(par->parent != 0) par = par->parent;
    return par->pid;
}

int sys_yield(void) {
	yield();
	return 0;
}
int sys_getlev(void) {
	return myproc()->lev;
}
int sys_setpriority(void) {
  int pid;
  int priority;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &priority) < 0)
    return -1;
  if(priority < 0 || priority > 10)
    return -2;
  return setpriority(pid, priority);
}
int sys_setmonopoly(void) {
  int pid;
  char* password;
  if(argint(0, &pid) < 0)
    return -1;
  if(argstr(1, &password) < 0)
    return -1;
  for(int i=0;password[i]!=0&&PASSWORD[i]!=0;i++){
    if(password[i] != PASSWORD[i]) return -2;
  }
  return setmonopoly(pid, password);
}
int sys_monopolize(void) {
  monopolize();
  return 0;
}
int sys_unmonopolize(void) {
  unmonopolize();
  return 0;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
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
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
