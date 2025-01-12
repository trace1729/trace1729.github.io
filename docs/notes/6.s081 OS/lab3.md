## Page Table

| 函数     | 作用                         |
|----------|------------------------------|
| copyin   | copy data to user space      |
| copyout  | copy data from user space    |
| mappages | install PTE for new mappings |
| walk     | find PA for VA               |


## XV6 Book

- 从3.5 开始， 都没读懂, 后续补上:  <13-04-23, David Chen> -

**implement pageing in practice** 

in `main.c` , it calls `kvminit`, and `kvminit`  calls `kvmmake`. `kvmmake` returns a pointer (kernel_pagetable).

kvmmake first init allocate a PAGE for root pagetable, and then call `mappages` to allocate memory for hardware
**(At this point, paging is not started, so virtual address is directed mapped to physical address)** 

`kvmmap` calls `mappages` , `mappages` first align the start address and end address, and start allocate PA for VA at page intervals

- `mappages` function makes me confusing
  * what is macro `PAGEROUNDDOWN` means
    + I guess this macro is used to align the size of a and size.



## lab 

### Speed up system calls

某些现代操作系统通过一个只读区域来在用户与内核之间共享数据，以加速系统调用的执行速度。这样的策略能够减少系统在地址转换上花费的时间。为了帮助你更好的理解如何向 `page table` 中插入映射，你的第一个任务就是为 `getpid` 这个系统调用实现这样的优化。

**Solution** 

The life cycle of a xv6 process is as follows.

We can call `allocproc` to create a new process. `allocproc` first use `kalloc` to allocate physical space for `p->trapframe` [](a) and `p->usyscall` .

```cpp

  if((p->usyscall = (struct usyscall *)kalloc()) == 0){
    freeproc(p);
    release(&p->lock);
    return 0;
  }

  p->usyscall->pid = p->pid;
```



Then `allocproc` call `proc_pagetabl` to initialize the pagetable for the process.

`proc_pagetable` use `uvmmap` to map virtual memory to corresponding physical memory.
 
```cpp
  // map a page for speed up syscall
  if(mappages(pagetable, USYSCALL, PGSIZE,
              (uint64)(p->usyscall), PTE_R) < 0){
    uvmunmap(pagetable, USYSCALL, 1, 0);
    uvmfree(pagetable, 0);
    return 0;
  }

  return pagetable;
}
```
 
We can call `freeproc` to free an running process. `freeproc` first use `kfree` to free process memory, Then call `proc_freepagetabl` to initialize free pagetable for the process.

```cpp
  if(p->usyscall)
    kfree((void*)p->usyscall);
  p->usyscall = 0;
```



`proc_pagetable` use `uvmummap` to  cancel mapping for virtual memory to corresponding physical memory.

And then call `uvmfree` to free pagetable.

```cpp

void
proc_freepagetable(pagetable_t pagetable, uint64 sz)
{
  uvmunmap(pagetable, TRAMPOLINE, 1, 0);
  uvmunmap(pagetable, TRAPFRAME, 1, 0);
  uvmunmap(pagetable, USYSCALL, 1, 0);
  uvmfree(pagetable, sz);
}
```

### Detecting which page have been accessed

> and according to the PA, find corresponding VA for kernel. But How to do this. Or we insert a new mapping for this
> copyin and copyout confused me. I guess they work as follows. copyin use process pagetable to find PA of the argument

实现的时候，只需通过 walkaddr 找到 用户虚拟地址对应的 物理地址，再对物理地址进行操作即可。 

> How to write content to corresponding addr

1. First we need to define `PTE_A` in `riscv.h` 
2. add stub for `walk` in `def.h` 
3. implement `sys_pgaccess` in `sysproc.c` 
    - 遍历就好 

<font color='red'> 注意我们不需要手动设置 PTE_A 位，硬件帮我们做好了 </font> 
```cpp
int sys_pgaccess()
{
    // lab pgtbl: your code here.

  uint64 va0;
  int num;
  uint64 usr_cnt;

  // 从 trapframe 获取参数
  if(argaddr(0, &va0) > 0) {
    return -1;
  }
  
  if(argint(1, &num) > 0) {
    return -1;
  }

  if(argaddr(2, &usr_cnt) > 0) {
    return -1;
  } 
  
  uint64 k_cnt = 0;

  // 向下取整，保证地址对齐

  va0 = PGROUNDDOWN(va0);
  struct proc* p = myproc();

  // 从 va0 -> va0 + num * pagesize 遍历 页表
  // 查看其 PTE_A 是否为 1
  // 为 1 的话，置结果第 1 << num 位 为 1，
  // 再将 access 位 置 0
  for (int i = 0; i < num; i++) {
    pte_t* pte = walk(p->pagetable, va0, 0);
    if (*pte & PTE_A) {
      k_cnt |= (1 << i);
      *pte = *pte & (~PTE_A);
    }
    va0 += PGSIZE;
  }

  copyout(p->pagetable, usr_cnt, (char* )&k_cnt, sizeof(uint64) / sizeof(char));

  return 0;
}
```

<++>


```json

