# The starting process of xv6

## Compile time

- Using gcc to compile all the kernel source file into a elf. 
- Using gcc to build userspace which contains all user program to `fs.img`, kernel can access this filesystem by using virtualized disk.
- Because the xv6 runs on qemu, qemu will read the meta data of compiled kernel, and put data segment in 0x8000000, and help virtualize the hardware resources the xv6 needs.

## Run time

- The first assembly code for kernel starts from `entry.S` (set by the `kernel.ld`), `entry.S` will set the stack_pointer, and call `start.S`.
- `start.S` will set relevent flags and set epc to `main`, then call `mret` to downgrade privliged mode to supervised mode.
- Then start `main.c`
 - init hardware resource, set up paging.
 - start first user program `initCode`, which using system call `exec` to call user-program `init`.
 - `init` print welcome message in the console, and wait for user input.

# 系统调用

## 宏观上

1. 在 user-space 设置好对应的函数声明，设置好系统调用号
2. 在 kernel-space 实现这个系统调用

## 微观上

The ecall instruction traps into the kernel and executes uservec,
usertrap, and then syscall, as we saw above. (ecall -> uservec -> usertrap -> syscall)

syscall (kernel/syscall.c:133) retrieves the system call number from the saved a7 in the trapframe
and uses it to index into syscalls. For the first system call, a7 contains SYS_exec (kernel/syscall.h:8), resulting in a call to the system call implementation function sys_exec.

syscall trace print the specified system call when executing
sysinfo add system calls to collect memory usage and processor count, user program can access this by using provided added system call.

# 内存分配器

xv6 原始的设计是所有进程共享一个内存分配链表，用一把大锁来保证原子性

改进后的设计是 每一个进程有自己独立的链表，当自己的空闲内存不够的时候，去其他cpu哪里获取内存。

# COW

在创建子进程时，我们设置子进程的页面映射为父进程虚拟页面对应的物理页面，并将二者的页表项都设置为不可写。

这样，fork 时就不会立刻复制内存，只会创建一个映射了。这时候如果尝试修改懒复制的页，会出现 page fault 被 usertrap() 捕获。

其次，我们还需要对 分配的页面做好 生命周期管理，可以为每一个分配的页面设置一个 计数器，当这个计数器归0时，也就是不再有其他进程
占有这个页面的时候，我们将分配的页面回收.


