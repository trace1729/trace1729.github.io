
# 总结

1.  [PA2.1](#org32c8d38)
2.  [PA2.2 有关 string 的处理](#orgd7766c4)
3.  [PA2.3](#org4b617b0)
4.  [待办事项](#org36ccb91)



<a id="org32c8d38"></a>

# PA2.1

NEMU 译码解析

    decode_exec 
    	|
    	|  (define INSTPAT_MATCH, INSTPAT_START)
    	|            |____ decode_operand (:func)  
    	|____ (a sequence of) INSTPAT (:macro)
    			| (4 个参数：匹配模式，指令名称，资料类型，资料动作)
    			|_____ pattern_decode (:func)
    			|			 (确定 key mask shift)
    			|_____ If match, execute INSTPAT_MATCH
    			|_____ then goto __instpat_end (这是一个tag)
    							|__ 这个是在 INSTPAT_START 
    								定义的一个东东

objdump 生成的反汇编是可读性最好的汇编代码，所以会包含一些伪指令，这些伪指令其实就是 base instruction 中的一种，(alias) 本身 伪指令是没有自己的byte representation 的。

高位低位的区别
  在使用 python 格式化指令的二进制表示时，注意 指令的最高位，存在python的字符串里，对应的是最低位。
比如对于0x12这个16进制数来说, 0001 是实际上的高四位。而当我们将其以字符串形式储存在 python 中时, s = bin(0x12) (s == '0x00010010')。保存 0001 对应的下标是 低四位，这个比较容易混淆。

hexdump 默认使用 big-endian 打印 bin 文件内容
xdd     默认使用 little-endian

假设一个文件包含 `` `\x14\x20` ``, 那么使用两种不同的二进制展示工具的结果如下

    hexdump:
    	2014
    xdd:
    	1420

我们接下来讨论一下，C语言无符号数的一些特性

```cpp
    unsigned x = -2147446780;
    // printf("%0x\n", x); // actually, is the starting address of the stack.
    int y = -4; 
    x = y; 
    unsigned t = 123;
    unsigned s = t + x;
    // 无符号数的溢出是 defined behavior, 自动归 0
    // 所以结果 小于 123
    // 另一种理解方式：在 无符号数 的运算规则下，4 对应的加法逆元是 2^n - 4
    // t + x = 119 + (4 + 2^n - 4) = 119 + 0
    printf("t(%u) + x(%u) = s(%u)\n", t, x, s);
    s = t * x;
    printf("%d\n", s);
    // s = t / x; 如果不强制类型转化, then x is promoted to unsignd 
    s = (int)t / (int)x; 
    printf("%d\n", s);
```

测试强制类型转换的时候是否会进行 sign-extending

    // nemu 之所以使用 bit field 就是为了能指定位数为符号位 (比如20，而非32或64)，这样
    // 在赋值给无符号数 进行 type promotion 时, 能按照指定位的值进行 sign extension
    // (i.e. 将第 20 位sign extend 到 32 位)  
    unsigned tmp = ({struct { int n: 8; } __x = {.n = -128}; (unsigned)__x.n;});
    printf("%u\n", tmp);

我们试着打印出4294967168的二进制表示，来看是不是真的进行的符号位扩展

```py
    print(bin(128))
    print(bin(4294967168))
    print(bin(1 << 12))
```

<a id="orgd7766c4"></a>

# PA2.2 有关 string 的处理

    strcat -----    memcpy---
                |            |
    	    |            |
    strcpy --> stpcpy --> mempcpy
                           |
    	               |
    strncpy --> stpncpy----- memset

总结 xxxcpy 都会调用相应地 xxpcpy。
xxpcpy 与 xxxcpy 的不同之处是：

-   xxpcpy 返回的位置是 dst + n
-   xxxcpy 返回的位置是 dst

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-right" />

<col  class="org-left" />

<col  class="org-left" />

<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<tbody>
<tr>
<td class="org-right">t(123)</td>
<td class="org-left">+</td>
<td class="org-left">x(4294967292)</td>
<td class="org-left">=</td>
<td class="org-left">s(119)</td>
</tr>


<tr>
<td class="org-right">-492</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
</tr>


<tr>
<td class="org-right">-30</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
<td class="org-left">&#xa0;</td>
</tr>
</tbody>
</table>


<a id="org4b617b0"></a>

# PA2.3

-   在生成elf文件的过程中，什么才算是符号？
    可以参考 csapp 第七章链接 P711
    <file:///home/trace/Documents/pdf/Computer.Systems.A.Programmers.Perspective.3rd.Global.Edition.2015.7-csapp(1).pdf>
    符号包括 全局变量和函数

-   在Linux下编写一个Hello World程序, 编译后通过上述方法找到ELF文件的字符串表, 你发现"Hello World!"字符串在字符串表中的什么位置? 为什么会这样?
    在 .rodata 区域 (read only data)

-   不匹配的函数调用和返回
    编译器对尾递归进行了优化

-   使用strip 去掉 `foo` 的符号表，能正常运行。
    但是去掉 `foo.o` 的符号表，链接失败。
    可能的原因：链接的过程需要参考符号表生成目标代码，而运行程序不需要了解这些信息。

-   如果 string 测试失败，make 为什么会返回 -1
    根据 man make, 如果有 makefile构建失败的话，会返回-1.

-   解释可执行文件的生成过程
    1.  首先由编译器将 AM 的实现打包成一个归档文件
    2.  其次将 目标源文件 编译成 目标文件
    3.  最后将 klib 也打包成归档文件
    4.  链接器根据 linker.ld 生成 可执行文件

-   为什么定义宏`__NATIVE__USE__KLIB`之后就可以把native上的这些库函数链接到 klib ? 这具体是如何发生的?
    -   gcc 会优先链接先出现的函数实现，开启 `__NATIVE_USE_KLIB__`, 我们自己定义的库函数会先于glibc在链接过程中出现

-   游戏是如何运行的
    从nemu的视角，用户按下按键，sdl 库检测到用户输入，将数据放在 nemu 指定的数据寄存器中。
    从应用的视角，内层的 while 循环通过 AM 提供的 `ioe_read` 读取到了 用户按下的键码 (`io_read` - `ioe_read` - `__am_device_function`)
    读取到键码后，应用程序将用户输入的键码和屏幕上展示的字母相比较
    -   如果一致，设置字母的内容为 NULL
    -   在下一个循环调用 `game_update` 更新界面(数组)。
    -   应用调用 `io_write` 将数据写入到 nemu 的指定地址。
    -   nemu 将数据提供给 SDL2 库，SDL2 库负责渲染界面。

-   如果在内层 nemu 运行，哪又是如何运行的
    流程是一样的只不过多加了两个步骤 应用程序 -> 内层 nemu 的 `io_read` -> 内层 nemu 的 `ioe_read`
    -> 外层的 `io(e)_read` -> &#x2026;

-   编译与链接
    -   在nemu/include/common.h中添加一行volatile static int dummy;
        然后重新编译NEMU. 请问重新编译后的NEMU含有多少个dummy变量的实体? 你是如何得到这个结果的?
        -   36个 riscv-linux-gnu-readelf -a xxx.elf |grep dummy
    -   添加上题中的代码后, 再在nemu/include/debug.h中添加一行volatile static int dummy;
        然后重新编译NEMU. 请问此时的NEMU含有多少个dummy变量的实体? 与上题中dummy变量实体数目进行比较, 并解释本题的结果.
        -   依然是 36 个，对于未赋值的静态变量，编译器会随机挑选一个使用。
    -   修改添加的代码, 为两处dummy变量进行初始化:volatile static int dummy = 0;
        然后重新编译NEMU. 你发现了什么问题? 为什么之前没有出现这样的问题? (回答完本题后可以删除添加的代码.)
        -   redefinition of dummy，对于未赋值的静态变量，是弱符号链接，多个相同的弱符号链接可以共存
            而强符号链接不行

-   Makefile 的工作方式

![img](https://image-trace.oss-cn-shanghai.aliyuncs.com/img/Pasted%20image%2020240121114911.png)


<a id="org36ccb91"></a>

# 关于 XV6
- [X] 熟悉一下项目，主要是 xv6 相关的，差不多忘光了。
  1. 写时复制是什么？
    - 在使用 fork 创建子进程时，子父进程共享空间，并设置权限为只读。
    - 在对只读内容进行写入时，会引发中断处理，在处理模块中，我们再为
     子进程的数据单独分配空间，写入数据。
     
  2. 如何改进的内存分配器
    - 原来是所有进程共同使用一个内存分配链表，一把大锁保平安。
    - 现在给每一个进程都有一个内存分配链表，这样可以减少 race condition。
   
  3. 网卡驱动获取/发送数据的流程
    - *发送* ：操作系统想要发送数据的时候，将数据放入环形缓冲区数组 tx_ring 内，然后递增 E1000_TDT，网卡会自动将数据发出。
    - *读取* ：当网卡收到数据的时候，网卡首先使用 direct memory access，将数据放入 rx_ring 环形缓冲区数组中，
             然后向 CPU 发起一个硬件中断，CPU 在收到中断后，直接读取 rx_ring 中的数据即可
         
  4. mmap 系统调用主要是干什么的
    - *初始化* ： 用户调用 mmap 的时候，找到一段连续的虚拟地址，并将文件内容映射到这块区域。
    - *记录*  ：  将映射关系记录到 vma 结构体中
    - *使用*  ： 日后出现缺页异常，首先看数据是否能在 vma 中命中，能找到的话就不需要访问文件了。

# 自我介绍

老师好，我是龚开宸，就读于南昌大学计算机科学与技术专业。	

我在本科期间做了不少计算机系统相关的公开课。比如伯克利的CS61C，和 MIT 的 6.s081。

CS61C 的内容主要是计算机体系结构，从高级语言入手，自顶向下逐步介绍计算机的硬件细节。这个课程有一个项目是
用 logisim 画一个 二级流水的 RV32IM 处理器。如今看来难度确实不大，但是也算我的处理器设计启蒙的作品。

6.s081 的内容是在教学型的操作系统xv6上，添加一些功能 比如说新的系统调用或者中断，或者对操作系统进行一些改进 比如
实现写时复制，减少创建进程时的开销。做这个课程主要是看一下在操作系统教材中抽象的概念是如何落实到具体代码实现中的。

在大四上我开始做一生一芯，到现在的话做完了单周期的 npc，正在写 PA3.1。(把这个 RT-Thread 接入后就准备写流水线了)

在这个这个过程中，我感觉最挑战性的部分还是写 npc。本来我觉的有 logisim 的经验再用 HDL 写一个应该会简单点吧。但是真正开始用 verilog 写的时候状况百出。这里主要是两方面原因，首先是 verilog 陈旧的语法特性。令我记忆犹新的，是一个信号的输入输出类型写反了，这个 bug 我找了三天，太痛苦了。现在想想，当时还是对 verilator 的仿真机制不熟，然
后没有称手的 verilog lsp 工具导致每次写完编译都有一堆 syntax error。(更不用说 verilator 的提示不算友好)。反正用 verilog 写完最简单的处理器之后我就转学 chisel。chisel 一开始学的也挺痛苦的，但是它毕竟有完善的编辑器和lsp，在镇痛期过后就爱上 chisel 了。

其次是对 HDL 适应，之前的高级语言几乎都是线性执行的，但是 HDL 主要描述的是电路之间的逻辑关系，对于组合逻辑来说，很多值的更新
都是同时发生的。从电路图到hdl连线的转化对我来说还是需要一定的时间。


# TODO 待办事项

-   [ ] 捕捉死循环
-   [ ] 实现声卡
-   [ ] 优化 litenes

