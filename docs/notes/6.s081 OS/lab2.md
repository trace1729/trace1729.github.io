## lab 2 kernal development

<!-- ```json -->
<!-- ``` -->
## 笔记 


### kernal / user mode
How would user actually override the bits that
identify context if the instruction to change that bit 
is itself a privilege instruction? It seems
user can never change to kernel mode.

- use `ecall` to invoke kernel mode


The loader loads the XV_6 kernel into memory at physical address 0x80000000. The reason it
places the kernel at 0x80000000 rather than 0x0 is because the address range 0x0:0x80000000
contains I/O devices

###  xv_6 
The startup process for xv_6 system

![](vx_images/4715621221272.png)
为了实现系统调用，我们首先需要获取用户传递的参数。由于最初是在用户模式下调用的调用的系统调用函数
，所以参数是储存在通用寄存器中。`kernal trap code ` 会保存通用寄存器的值，`kernal code` 就可以利用 trapframe 来获取参数。xv6 为此封装了`argint`, `argaddr`, `argfd`三个函数。
  
- 使用它们可以分别以 整形，指针，文件描述符来获取用户传递参数
- 它们都借助 `argraw` 来从正确的寄存器获取参数

## 实验


### trace system call

#### 系统调用的执行过程

1. `user.h` add function stub to pass compiling 
2. `usys.pl` generate corresponding assembly code 
3. `syscall.c` call corresponding function in `sysproc.c` 
  - add code in `sycall.h` `1 << xxx` 
  - add function `sys_trace` in `sysproc.c` 
  - add `extern uint64 sys_trace(void)` function signature
  - modify array `syscalls` 

### sysinfo system call

- need record
  * `freemem` free memory, `kalloc.c` 
  * `nproc` number of process, `proc.c` 

- copy `struct info` back to user space
  * `sys_fstate` in `sysfile.c` 
  * `filestat` in `file.c` 


- quesion

1. why we need copy `struct info` to user space 

- because after the system call, we need read struct info in user space

2. why testmem test failed?

- seems like the freemem is always 0

    `p = p->next` instead of `p++` 
