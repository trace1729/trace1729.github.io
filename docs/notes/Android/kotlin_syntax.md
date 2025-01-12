## kotlin_syntax
## lambda expression 
In `kotlin`, lambda expression is widely used, now let us dive into 
this feature.

Suppose we want to get the item that has max lenghth in a list,
we might write the following code
```java
val list = listOf("Apple", "Banana", "Orange", "Pear", "Grape", "Watermelon")
    var max = ""
    for (fruit in list) {
        if (fruit.length > max.length) {
            max = fruit
        }
}
```
actually the above code can be shorten to oneline
```kotlin
max = list.maxBy { it.length }
```

So, How does it work?
- First, we need to know that maxBy actually takes a lambda function as an
its arugment. In kotlin, if tha lambda expression is the only argument for a
funtion, then the lambda expression could be extract outside, and parentheses
could be omitted.(if the function have more than one argument, then we should keep it.)

- Ok, now we know, maxBy actually take a lambda, So what is the lambda function
we are looking for. You could think about how `maxBy` are implemented

```kotlin
T maxBy (lambda f) {
    max = ""
    for (l in list) {
        if (f(l) >f(max)) {
            max := l
        }
        
    }
}  
```

Well, the function simply takes in an item, and return its length.
Ok, now we could start to write the lambda
```kotlin
val lambda = {f: String -> f.length}
    
max = list.maxBy(lambda)
=> max = list.maxBy({f: String -> f.length})
=> max = list.maxBy(){f: String -> f.length}
=> max = list.maxBy {f: String -> f.length}
=> max = list.maxBy{it.length}
```
it reads, for every elemnet in a list, we will apply lambda and perform
that function

## Java 函数式 API 的使用
```kotlin
new Thread(new Runnable() {
@Override
public void run() {
    System.out.println("Thread is running");
}
}).start();
=> 
Thread(object : Runnable {
override fun run() {
  println("Thread is running")
}
}).start()
=>

Thread(Runnable {
    println("Thread is running")
}).start()

=> (由于函数列表只有一个 接口)
Thread({ 
    println("Thread is running")
}).start()

=> (由于 lambda 是唯一一个参数)
Thread {
    println("Thread is running")
}.start()
```


## 非空检查, with, let, apply 
### 非空检查
`?.`, `!!`, `?:` 
```kotlin
fun getTextLength(text: String?) = text?.length ?: 0
val upperCase = content!!.toUpperCase()
```

### let
```java
fun doStudy(study: Study?) {
    study?.let {
        it.readBooks()
        it.doHomework()
    }
}
```
actually it is 
```kotlin
void let() 
{
    for (s in study) 
    {
        s?.some_function
        s?.some_function
        ...
    }
}
```

### with apply run 
```java
val result = with(StringBuilder()) {
    append("Start eating fruits.\n")
    for (fruit in list) {
        append(fruit).append("\n")
    }
    append("Ate all fruits.")
    toString()
}

? with(object, f: lambda) 
{
    f(object)
}
```
```java
val result = StringBuilder().run {
    append("Start eating fruits.\n")
    for (fruit in list) {
       append(fruit).append("\n")
    }
    append("Ate all fruits.")
    toString()
}
```

```java
val result = obj.apply {
// 这里是obj的上下文
}
// result == obj
那么现在我们再使用apply函数来修改一下吃水果的这段代码，如下所示：
val list = listOf("Apple", "Banana", "Orange", "Pear", "Grape")
val result = StringBuilder().apply {
    append("Start eating fruits.\n")
    for (fruit in list) {
        append(fruit).append("\n")
    }
    append("Ate all fruits.")
}
```

### Summary
if we want to perform some actions on the list of objects, we could use `let` funtion

if we want to perform some operation on the spercific objects, we could use `run` , `apply` , `with` .

