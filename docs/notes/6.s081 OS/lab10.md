### mmap

mmap 将 文件内容 映射到虚拟内存。这样操作系统可以通过虚拟地址来对文件进行修改。

需要查看的内容
    - lecture 15 17 19 VMA
    - lazy page allowcation
    - 垃圾回收机制

lecture 10

结束 lab 后(除了 lock)
    - paper
    - lecture

什么叫 fill in the page lazily, 哪里的 page

process 将 打开的文件保存在 p->ofile 数组中，可以通过 file descriptor 来访问。

那么在之前，uvmcopy 是通过查找 起始地址对应的 页表项 来做地址映射的。
mmap 的重点是要找到连续的内存空间来存放文件映射区域。

naive thought: 
	在调用 mmap 时，使用循环便利整个虚拟地址空间，找到连续 n 个 page；
	为这连续的 n 个page 设置标志位。并记录在数组 vma 中。
	随便找一段空闲内存好像不显示，会出现各种权限错误。

地址空间
addr
	user space
		text data bss heap {mmap area} stack 
	  kernerl space

- 首先，只是为 mmap 在*用户空间* 找到一个连续的空间，然后注册一下 vma。这个时候不对虚拟内存做任何操作
缺页中断的时候，再做页面映射。

- 不知道从虚拟内存的那一个位置开始查找页面映射，去看下 exec 的代码试试。

> 发现可以从 p->sz + 2 * PGSIZE (用户栈) 开始。(其实从0开始扫描也行)

- 程序卡死了
- 逆天, 是因为在 trap 中 判断是否发生了缺页，但是没有对缺页做任何处理。。。

- 在对 vma 进行中断处理之后，相同的va 再次触发了缺页中断，这导致 mappages 出现 panic。我猜测大概是因为我对 权限位没有处理好

> 确实，prot 需要右移一位，才能和 pte 标志位相对应

- 修正后，出现 panic freewalk, 估计是 进程结束时，没有释放掉 vma 所指向的 虚拟内存；
	先查看一下写入的数据对不对。

- 并不是，因为 mmaptouch 出现了问题，设置 p->killed = 1，所以才会触发 freewalk
第二个页面只读到 2048 字节的数据, 将多余的数据初始化为0就好了。

让我好奇的是， write(fd, buf, BSIZE) 是怎么做到每次写入一个字符的？
他的写入大小不是 BSIZE 吗？

- 在内核态只能连续检验一个页的内容。 (不同的页需要查页表获得映射)
