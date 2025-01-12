---
title: CS61C 1
date: 2022-08-01 10:35:27
tags: CS61c
mathjax: true
---
## ISA 的概念

### RISC 和 CISC

上世纪有两种流行的计算机组织结构

* CISC **Complex Instruction Set Computer**

  The main idea behind this is to make hardware simpler by using an instruction set composed of a few basic steps for loading, evaluating, and storing operations just like a load command will load data, a store command will store the data

* RISC **reduced Instruction Set Computer**
  
  The main idea is that a single instruction will do all loading, evaluating, and storing operations just like a multiplication command will do stuff like loading data, evaluating, and storing it, hence it’s complex.



基于这两类组织结构，硬件工程师开发了多种不同的指令集(ISA)

### ISA example

* 基于 CISC 开发

  * Intel x86
* 基于 RISC 开发

  * ARM
  * RISC I - V 

    > 1981年 由 berkelay
    >

  * MIPS

## RISC 

* risc设计思想是当前芯片设计的主导
* 目前 intel x86 的底层也使用了 risc 的思想，即将一条复杂的指令拆分成多条简单指令执行

## RISC V
### registers
* RISC V 由32个寄存器 $x_0$ - $x_{31}$组成
* 可以使用 **数字** 或者 **寄存器名** 来引用寄存器
     - 保存变量名 
     $s_0$ - $s_1$ <=> $x_8$ - $x_9$,

     $s_2$ - $s_{11}$ <=> $x_{18}$ - $x_{27}$
     - 保存临时变量
     $s_0$ - $s_2$ <=> $x_5$ - $x_7$,

     $s_3$ - $s_{6}$ <=> $x_{28}$ - $x_{31}$
* $x_0$ 是 **0寄存器**, 其值永远是 $0$
* 存储在寄存器中的数值 **没有** 类型之分，数值的类型取决于对数值进行的操作
     
     
### 指令

**Instruction Syntax is rigid:**
**op dst, src1, src2**

- 1 operator, 3 operands
  - op = operation name (“operator”)
  - dst = register getting result (“destination”)
  - src1 = first register for operation (“source 1”)
  - src2 = second register for operation (“source 2”)

#### 算数指令

c: `a = (b + c) - (d + e)`

risc: 
```risc
add s0 t1 t2 # b+c
add s1 t3 t4 # d+e
sub s2 s0 s1 # (b+c) - (d+e)
```

#### 立即数

c: `a = c + 5`

risc: `addi s0 s1 5`

#### 数据传输指令

**Instruction syntax for data transfer:**

- memop reg, off(bAddr)
  - memop = operation name (“operator”)
  - reg = register for operation source or destination
  - bAddr = register with pointer to memory (“base
  address”)
  - off = address offset (immediate) in bytes (“offset”)

c: `a[10] = a[3] + b`

risc:
```
  lw t0, 12(s3)     
  add t0 s1 t0
  sw t0, 40(s3) # 将t0 存入 s3
```
**大端小端**

- 大端
  > Most-significant byte at least address of word
- 小端
  > Least-significant byte at least address of word

risc v 使用的是 小端法

**字节操作** 

For example, let s0 = 0x00000180:

```
lb s1,1(s0)
lb s2,0(s0)
sb s2,2(s0)
48
# s1=0x00000001
# s2=0xFFFFFF80
# *(s0)=0x00800180
```
注意细节

- 小标从0开始
- 由于数据以小端方式存储，引用数据是从地位向高位计算子节数
- 一个子节8位 => 两位16进制
- 注意符号扩展  


#### 条件判断
- Branch if equal
  - beq reg1, reg2, label
  - if v(reg1) == v(reg2)
  - go to label 
- Branch if not equal
  - bne reg1, reg2, label
  - if v(reg1) != v(reg2)
  - go to label 
- Branch if less than
  - blt 
- Branch if greater than or equal 
  - bgt
- jump
  - j label
  - unconditional jump to label

<div class="note info">
  <p>
  In cpp
    ```c++
    if (i ==j) a = b
    else a = -b
    ```
  </p>
  
  <p>
    In risc 5
    ```bash
    # i -> s0, j -> s1
    # a -> s2, b -> s3
    beq s0, s1, then

    else:  # if true
      sub s2 x0 s3
      j end

    then: # if false
      add s2 x3 x0
      j end

    end:
    ```
  </p>
</div>

#### 移位操作

- 逻辑右移 在左边补0
- 逻辑左移 在右边补0
- 算数右移 在左边补1

![image](1.png)


### some tips

<div class="note primary"><p>
  `op` 指令 与 `op+i` 指令的区别在与 后者第三个参数为立即数而非寄存器</p></div>
<div class="note warning"><p>
  注意没有`subi`指令</p></div>


