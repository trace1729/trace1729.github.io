## lab 6 multithreading

## XV6 Chapter 7 Scheduling 

7.6 - 7.7 没有看

### 进程调度的 6 个问题

#### 7.1

1. 如何在进程间进行切换
2. 如何实现对于用户透明的上下文切换
    - `yield` , `swtch` , `scheduler` 
3. 需要加锁来防止 race condition
    - `p->lock` , `sleep` , `wake up` 
4. 进程结束时需要释放掉所有资源，仅依靠进程自己不能完全释放。
    - `wait` and `exit` 
5. 多核机器必须知道他正加执行的是哪一个进程
6. sleep and wake up

`swtch` only save and restore 32 regs 

为什么 process 有 context, cpu 也有 context, 他们是用在不同的场景下吗 


#### 7.2 code context switching


复习一下在 chapter 4 中，中断的调用过程

1. `usertrap` calls `yield` 
2. `yield` calls `sched` 
3. `sched` calls `swtch` to save current context in p->context, and switch to the scheduler context previously saved in cpu->scheduler

Q: 为什么要切换到 `scheduler context` , `scheduler context` 又是什么意思？
A: 每一个 cpu 都有一个 kernel thread 运行 `scheduler` 函数。想要切换执行的进程，就要先切换到这个运行着 `scheduler` 函数 的 kernel thread. 再通过 
`scheduler` 函数来进行进程切换。(对应4次转换的第二次)




#### 7.3 scheduler

Q: 为什么在`swtch` 执行期间，要保持 `p->lock`
A: 因为要维持一个不变量，也即 before schedulering, process must excute `yield` , `sched` , `scheduler` continuosly. 不加锁的话，可能在cpu1 中 进程p 刚将自己的状态设置成 runable ，与此同时 cpu2 看到 进程p的状态是 runable，就想要开始执行这个进程。这样会导致两个cpu 运行在同一个 kernel stack 中 


#### 7.5 sleep and wake up


为什么不在 sched 之前 release p-lock

In the given code, we don't release the `p->lock` before calling `sched` because releasing the lock before calling `sched` would allow *other* threads to modify the state of the process (`p->state`) or wake it up (`wakeup`), which could lead to race conditions or incorrect behavior.

不太对劲，之后问问别人

#### 7.8 wait exit and kill

**wait** 

1. free any child whose stauts is ZOMBIE

**exit** 

1. put caller into zombie state.
2. wake up parent

**kill** 

does very little, just mark the state of process to be `KILLED`` `. when the process enter or exit the kernel, the trap handler will see the flag and free this process.
    

### Lab thread

#### user level thread package

1. 创建的时候. 初始化 context, 设置 ra 和 sp 两个指针.
2. 调度的时候, 保存 ra, sp 和 callee saved 寄存器

lab 很简答,但是我很疑惑

Q: 我只是设置了线程结构体中context的ra值,操作系统是怎么知道要加载这个ra到pc的.如果是进程的话,编译器会帮助自动生成相关的汇编代码(比如将ra寄存器的值放进pc里), 但是这个 thread 是怎么做到的??
A: 傻了, thread_Switch 就有 `ld ra, xxx`. 把保存的 ra 值加载到 ra 寄存去了。最后执行ret, 就把 ra 的值给pc了。

#### 使用线程

在这个任务中，你将探索如何使用线程和锁来保证哈希表在多线程下正常工作。你应该在真正的Linux或者Macos 下
完成这个实验 (not xv6)

这个实验使用了 `pthread` 线程库，你可以阅读文档以了解库的使用。

文件 `ph.c` 实现了一个在单线程下正常工作，但在多线程下会出错的哈希表。

你需要做的，就是使用一把互斥锁，来使得哈希表在多线程的情况下能够正常工作。

在调用 insert 函数前后加上一把 互斥锁就可以了。


    pthread_mutex_lock(&lock);
    insert(key, value, &table[i], table[i]);
    pthread_mutex_unlock(&lock);

注意不能在 insert 函数内加锁，因为在向 insert 函数传递值的时候(链表头)，
可能会发生 race condition.

#### barrier

实现一个类似 sleep 和 wakeup 的机制

比较简单, 当有线程进入 `barrier` 的时候,递增 `barrier.nthread` , 如果 `barrier.nthread` 是 `nthread` 的整数倍,说明在当前轮的所有线程都到达了 `barrier` , 这个时候就调用 `broadcast` . 不然就 `wait` . 注意在两个出口都需要更新 round

```cpp

static void 
barrier()
{
  // YOUR CODE HERE
  //
  // Block until all threads have called barrier() and
  // then increment bstate.round.
  
  pthread_mutex_lock(&bstate.barrier_mutex);
  bstate.nthread++;
  if (bstate.nthread != 0 && bstate.nthread % nthread == 0) {
    pthread_mutex_unlock(&bstate.barrier_mutex);
    pthread_cond_broadcast(&bstate.barrier_cond);
    bstate.round = bstate.nthread / nthread;
    return;
  }
  pthread_cond_wait(&bstate.barrier_cond, &bstate.barrier_mutex);
  bstate.round = bstate.nthread / nthread;
  pthread_mutex_unlock(&bstate.barrier_mutex);
}

```



