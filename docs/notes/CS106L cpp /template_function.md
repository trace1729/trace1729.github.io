# About template
- How to write template function in a class

    write **implematation**  in the header file
## 配置问题

1. vscode 不能进行代码补全

    1. 可能是include 的路径没有设置好

        使用 find . -name "cpr*" 找到当前文件下包含cpr 的路径

        在c++ 设置中，在include path 中添加 

        ![image](assets/image-20221013082315-t7196s2.png)​
2. cmake 报错 

    * cpr_Dir not set  
        
      在 cmakelist 里 加上 `set(cpr_DIR "./vcpkg/installed/x64-linux/share/cpr")`​
    * Could NOT find CURL (missing: CURL_LIBRARY CURL_INCLUDE_DIR)  
      `sudo apt update && sudo apt upgrade && sudo apt install curl && sudo apt-get install libcurl4-openssl-dev`​

## Lec 5,6 STL lib

### sequence data structure

### associative data structure

* map, set
* shared method:

  *  count(key) : 统计 含有key的元素数量
  *  find(key):   返回 指向 key的迭代器

### std lib

```c
std::find() return iterator
std::sort(begin(), end()) return none
std::fill(begin(), end(), 10) return none
std::copy(begin(), end(), container) return none
std::lower_bound()
std::upper_bound()
std::accmulate(begin, end, 0 / 0.0) // 注意 浮点数使用 0.0
```

### bug

std::find 函数需要 algorthim 头文件

## Lec 6 classesp

### a bug

* 出现的问题

  ```c
  student.cpp:5:18: error: definition of implicitly-declared ‘Student::Student()’
      5 | Student::Student() {
        |                  ^
  ./build.sh: 4: ./main2: not found
  ```

* 在 .cpp 文件定义了 构造器，但是没有在头文件定义

### a tip

我们不需要手动执行 ~constructor 当没有任何一个元素指向这个对象时，系统会自动销毁

## Lec 7 template

* class / typename
* 为 泛型类 写 泛型函数的时候，命名空间要加上 generic typenames
* 写泛型类时，要在.h 文件里 引用.cpp 文件，而不是 在.cpp文件里引用 .h 文件 (multiple definiton)

### some tips

* Add template<class T1, T2..> before class definition in .h 1.

  > 在头文件中类的定义前加上 template
  >

* Add template<class T1, T2..>before all function  
  signatures in .cpp

  > 在模板类的每一个函数前加上 泛型声明
  >
* When returning nested types (like iterator types), put typename  
  ClassName<T1, T2..>::member_type as return type, not  
  just member_type

  > 如果返回类型(we call it return type) 本身也包含泛型，我们需要将其改写为 (typename className::return_type)
  >
  > ```c
  > //比如
  > template <typename T>
  > iterator myVector<T>::cbegin() const {
  >     return elem;  
  > }
  >
  > ||
  > ||
  >   
  > template <typename T>
  > typename myVector<T>::iterator myVector<T>::cbegin() const {
  >     return elem;  
  > }
  > ```
  >
* Templates don’t emit code until instantiated, so #include the  
  .cpp file in the .h file, not the other way around!

  在头文件末尾包含 .cpp 文件，不要在.cpp 文件中包含头文件
