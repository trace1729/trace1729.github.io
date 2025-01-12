## Chapter 5 device interrupt

a top half
    process kernel stack, system call (模式切换，数据拷贝)
a bottom half
    hander 如何接受数据


`consoleinit` configures two *interrupt* . One is receive interrupt, another is (receiving) complete interrupt.

**How to Read**  (software)

`read` system call make their way through `consoleread` , `consoleread` waits for input to arrive, and store input in cons.buf.

**How UART handle input** (hardware)

user type -> hardware asks for a interrupt. -> trap handler( `trap.c` ) check if it is device interrupt  -> devintr according to `scause` (and Plic),  calls `uartintr` . 

`uartintr` read any chars to `consoleintr`. if user have typed entire line.`consoleintr` wakeup `consoleread`.

once `consoleread` read a whole line from cons.buf, it copy contents to user space and give control back to user.

**How to write** 

**timerintrrupt** 

only in machine mode, in `start.c` 

### 实验

**为E1000网卡加一个驱动** 

- 框架代码解析。首先是 `kernel/net.c` 存放是一些有关 `mbuf` 的 库函数，针对 `mbufq` 的一些操作。实验里用不到。
- `kernel/net.h` 存放的是`mbuf` 结构体的定义和一些宏函数。
- `kernel/def_net.h` 存放的是一些E1000寄存器的宏
- `kernel/e1000.c` 存放是有关 e1000 网卡 初始化，存储，转发的函数。

**实现 `e1000_tranmit` 函数**

> free the last mbuf that was transmitted from that descriptor

Q:不太清楚这个 **last mbuf**  到底存放在哪里

A:放在 tx_buf array

>  stash away a pointer to the mbuf for later freeing.

Q: 这个 **stash away** 是要把这个buf指针存放在哪里呢？

A: 存放在 tx_buf array

