## operator overloading
There are two types of overloading, one is **Member function** overloading, 
that is,  the overloading funtion belongs to the class(instance), 
this overloading funcion overloading can directly access inner private varible

```c++
//fraction.h

bool operator < (const Fraction& rhs) const;
```

The above funtion override the **<** operator, takes the 
variable that is on the right hand side of the operator as 
arugmnet, compare to it, and return the result.
```c++
//fraction.cpp
// because it is a member function, we need to add `Fraction::`
// to specity the namespace of the faction (differ funtion from different class)
bool Fraction::operator < (const Fraction& rhs) const {
    return rhs.denom * num < rhs.num * denom;
}
```
The other is `non member funtion`, You may wonder why we
need `non memeber function`. Well, consider a stiatuon, when 
you want to compare two different types 
 - e.g. we want to compare a double and a Fraction

we cannot use member funtion since the LHS is not a fraction at all.
OK, we then introduce how to write `non member function`
```c++

friend Fraction& operator += (Fraction& lhs, const Fraction& rhs);
friend bool operator < (const double& lhs, const Fraction& rhs);
friend std::ostream& operator << (std::ostream& out, const Fraction& target);
```
since non-member function does not belongs to the class,
it is not possible for it to directly access private varivable 
of the arugment passed in. To achieve this goal, we need to add
a `friend` descripnator in **function declaration**

<font color='red'>do not add `friend` </font> 
in the **function implementation**

```cpp

Fraction& operator += (Fraction& lhs, const Fraction& rhs) {
    lhs.num = lhs.num * rhs.denom + lhs.denom * rhs.num;
    lhs.denom = lhs.denom * rhs.denom;
    lhs.reduce();
    return lhs;
}
// Implementing the * operation in a non-member function
bool operator < (const double& lhs, const Fraction& rhs) {
    return lhs < (double)rhs.num / rhs.denom;
}
// Overloading << to allow for passing Fractions into streams.

std::ostream& operator << (std::ostream& out, const Fraction& target) {
    out << target.num << "/" << target.denom;
    return out;
}
```
## special member function
```cpp
class Widget {
 public:
    Widget(); // default constructor
    Widget (const Widget& w); // copy constructor
    Widget& operator = (const Widget& w); // copy assignment operator
    ~Widget(); // destructor
    Widget (Widget&& rhs); // move constructor
    Widget& operator = (Widget&& rhs); // move assignment operator
}
```
- 默认构造器
- 拷贝构造器  (传参的时候)
-

## difference between assignment and initilize list
When you initialize fields via initializer list the constructors will be called once.
If you use the assignment then the fields will be first initialized with default constructors 
and then reassigned (via assignment operator) with actual values.


## on delete and on default
- `on delete` tell compiliers do not generate SMF functions for we want to write our own
- `on default` tell compiliers keep SMF functions when we want to write our own

