## week2 类与对象

**定义是声明的一种** (defination is a type of declartion)

- 如果只给出函数声明，没有给出函数体，那么这就只是声明，不是定义。
- cpp 允许一个变量被多次声明，但是只能被定义一次。

```cpp

extern int i;
extern int i;
```

像上述情况是被允许的

**成员、this、类型别名** 


```
member-specificaton
    member-declartion member-specificaton
    access-specifier: member-specificaton
```


c++11 引入了 `using` 来代替 `typedef` 使用
`using` 定义的别名同样也受 `access-specifier` 的控制。


类内的成员函数都有一个隐式参数，这个隐式参数是指向成员函数所属对象的指针。

```cpp
class Foo {
    int a;
    void bar() {
        a += 1;
    }
    // 实际上
    void bar(Foo* this) {
        this->a += 1;
    }
}
```

**inline substisution** 

由于函数调用有开销，编译器会将类内成员函数内联替换 (inline substisution)。
所谓内联替换，就是指将 函数内容原地展开

早期使用 `inline` 关键字可以增大编译器将函数进行内联的可能，现代编译器可能不会管这个声明了。

*Compiler: Nobody knows inline function more than I do*

**构造函数** 

如果一个成员变量同时被 member initializer list 指定且有 default member initializer，按前者执行，后者被忽略。
所以，如果你希望一个变量的值为默认值，就不要写在 default member initializer

## week 3

**拷贝赋值运算符 (copy)** 

在我们使用 `a = b` 类似的语句时，我们其实在调用 `.operator=(elem foo)` 函数。
和构造函数类似，如果用户没有重载一个类的构造函数，那么cpp会生成一个默认的 `.operator` 函数。
这个函数在赋值时，默认调用成员的 `.operator` 进行赋值。

**运算符重载** 

**引用** 

当对象所占用内存空间很大时，在函数传参数时做值传递很浪费空间, 这个时候可以传递指针或者引用。
引用就是一个对象的别名。比如

```cpp
int x = 1;
int & y = x;
```

之后对 `y` 的操作就等同于对 `x` 的。

```cpp
y = 3; // x = 3
int z = 4;
y = z; // x = 4 注意到这里并不是将y绑定到z，而是将z的值赋值给y说引用的对象x。
```

回到最初的话题，我们知道在c语言里，可以使用指针来避免参数传递所带来的内存浪费，哪又何必再引入引用呢？
这就和上节课所讲述的 运算符重载有关系了，考虑下面一个例子。

```cpp
// Matrix.c

Matrix operator-(Matrix other) {
    ...
    return *this;
}

Matrix m1, m2;

//... initilizing m1 and m2

auto m = m1 - m2;
```

我们重载了矩阵类的减法操作, 重载函数的参数是 `Matrix` 类型的。上面我们提到过，直接值传递会造成巨大的内存浪费。而这里要使用指针进行重载的话，会显得不直观。

```cpp
// 如果使用指针类型进行重载

auto m = m1 - &m2;
aut0 m = &m1 - &m2;
```

所以我们就引入了引用这个运算符。

```cpp
Matrix operator-(Matrix & other) {
    // other 就是 m2 的一个别名，传参过程中没有进行拷贝操作
}

auto m = m1 - m2; 
```

引用(&)与 c 语言中的 `type * const` 类型 , 它只能改变所指向对象的值，而不能自身的指向。
我们可以对引用进一步限制，`const type &` , 这样引用对象即不可以改变所指向对象的值，也不能改变自身的指向。(
类似 `const type * const` ) 

**about const**

* 如果成员函数没有改变类内属性的值，则应该给其加上const 标签
* const iter: 可以改变 iter 所指向的值，不能改变指向
* const cons_iter 可以改变指向，不能改变值

- const 成员函数实际上是给编译器提供的一个保证，如果一个 类的类型是 const, 那么调用 const 方法 problem保证不会修改这个类的内容。
- const 与 非 const 成员函数是可以共存的，前者 编译器隐式传入的参数是 T* this, 后者是 const T* this

## week 4

标准转换
用户自定义转换

> 为什么要引入 用户自定义转换 ?

来看下面一个例子

> 注意 如果是将 函数声明和实现分开写的，且声明指定了方法为 const， 那么实现里的函数头也要指定为 const

copy elision 

如果一个函数返回的是和返回类型相同的临时值，那么拷贝会被省略
如果一个函数返回的是和初始化表达式类型相同的临时值，那么拷贝会被省略

```cpp
T f() {
    return T();
}

int main() {
    f();
}
```
没有优化的时候，会在 f() 内调用一次 默认构造函数 得到临时对象1。
之后在 main 使用 临时对象2 的拷贝构造函数 调用 临时对象1 完成构造。

优化后
直接在返回时进行默认构造。

rule of three:
rule of zero: 

## week 5, 6

模板和元编程
具有看 cpp reference 学习的能力

容器和算法是相互独立的，迭代器是在两者沟通的桥梁。

ptr++ 和 ++ptr 这两者的运算符重载稍有区别

**泛型编程与模板** 

通过继承实现泛型和通过模板实现泛型有什么区别

Java 的设计是，任何对象都继承于 Object 对象，这样任何容器都可以这个基类作为其成员的类型。
Cpp 不同 与 java 没有采用单根结构，而是通过引入模板实现泛型。

> 显然，类模板本身不是一个类，仅包含模板定义的源文件不会生成任何代码。当我们要使用这样的模板时，我们应当指明其参数，*编译器会根据参数和模板生成出一个实际的类*（我们称这个类为对应模板的一个 特化 (specialization)；这个过程叫做模板的 实例化 (instantiation)（对函数模板而言也一样）

**STL 容器** 

**Alogrithm 库** 

比较重要的有 
- `upper_bound` , `lower_bound` 这对函数可以在指定范围内找到一个数的上界和下界 (左开右闭区间)
- `count` 
- `find` 
- `sort` 

**迭代器的分类** 

Sequential container:

- array: contiguous 
- vector: contiguous
- deque: Input  <font color='red'> Random Access </font> 
- forwardlist: Forward
- list: Bidirectional

Associative container:
- map, set, multimap, multiset: Forward <font color='red'> Bidirectional </font>

unassociative container:
- unordered_map, unordered_set, unordered_multimap, unordered_multiset: Input <font color='red'> Forward </font> 

迭代器的分类不是一种类型，而是一种要求。迭代器是泛型函数对传入参数要求的统称。

**函数对象** 

函数指针，以及重载了 function call operator operator () 的类的对象。事实上，C++ 将任何定义了 function call operator 的对象统称为 函数对象 (Function Object) 。


### week 7 左值右值 移动语义 完美转发

**左值右值** 

什么是表达式 (expression)

Primary expressions
- this
- 字面量
- id-expressions
- lambda
- fold-expressions
- require-expressions

什么是语句 (statement)

表达式具有什么样的性质

- 类型。比如 `int n = 1`, n 的类型是 `int` . 字面量 `1` 的类型也是 `int` 
- 分类 
    - `lvalue` 表征一个对象的表达式 (n)
    - `rvalue` 不与对象关联的表达式 (1)

视频从汇编层层面阐述了 区分左值右值 可能带来的优化, 有助于理解概念。

展示了在 cpp 中哪一些具体的表达式是
- lvalue (除了枚举类，其他有名字的都是左值)
- rvalue (除了字符串字面量，其他常量都是右值)

**右值与将亡值** 

pvalue -> pure value 没有名字, 一般不占据内存
xvalue -> eXpired value 临时占据内存


**移动语义**

move sementics
- 移动构造
- 移动赋值

为什么要引入移动赋值？
例子：

运算优先级

copy-elision -> move assignment
            -> copy assignment

精确定义什么是 *临时* -- **能否复用资源**

```cpp
template<class T>
void swap(T& a, T&b) {
    T tmp(a); // 拷贝构造
    a = b; // 拷贝赋值
    b = tmp; // 移动赋值 (因为 tmp 在之后就被销毁了) 错误的，仍然是拷贝赋值，因为 tmp 有名字。
}
```
SMF
- 构造函数
- 析构函数
- 拷贝赋值
- 拷贝构造
- 移动赋值
- 移动构造

共性:
    如果用户自己没有定义 smf， 而在代码中又使用了，编译器会自动生成 默认的 smf.
    你也可以指定删除一个smf (= delete)。注意如果你声明某个 smf 为 删除，这不仅表示你想要删除编译器默认生成的 smf，而是表示你不需要使用这个 smf (也就是说，你不能自己定义)。


**materialization** 
    将一个 pxvalue -> xvalue
    可以通过将 prvalue 绑定给一个 const 引用，
    也可以将 prvalue 绑定给一个 右值引用

**copy elision**

```c++
Foo baz() {
    Foo f;
    return f;
}

int main() 
{
    Foo f = baz();
}
```
上面这段代码的执行步骤可以分为三步

1. baz 函数内部使用构造函数创建一个 Foo 对象，并尝试以 移动形式 返回
2. 我们记函数调用表达式的值为 __call_expr, Foo __call_expr = std::move(return_value)
3. Foo f = __call_expr。由于 __call_expr 是一个 prvalue, 会触发 移动构造

重点是理解 __call_expr 这个中间过程
<!-- ____ -->

**完美转发 perfect forwarding**

见 `container.cpp` 代码

### week 8 智能指针

智能体现在?

- 自动回收资源
- 可以强制要求指针不为空
- 更多的安全检查和限制

**unique pointer** 

- 是对象的拥有者，并假设是唯一的所有者
- 自动回收资源
- 只能移动，不能拷贝

std::unique_ptr<HelperType> ptr = std::unique_ptr<HelperType> ( new HelperType() );
auto ptr = std::make_unique<HelperType>(Args ...)

## 困惑
Q: 假设有代码 `Foo bar() { return Foo(); }`,  `Foo f = bar();` 为何这里的 bar 是 prvalue, bar() 它不是占据内存吗 ?

Q: void may_share( const shared_ptr<widget>& ) 传递一个 const 对象，又如何对 cnt 进行修改呢

因为 shared_ptr 本身并不储存 cnt, 还是单独开辟了一块内存储存 cnt，shared_ptr 本身存储的是指向内存的那一块地址，
在递增cnt的同时，这个地址并不改变。
