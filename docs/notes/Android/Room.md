## procedure
### add dependencies
[room dependencies](https://developer.android.com/codelabs/basic-android-kotlin-compose-practice-bus-schedule-app?continue=https%3A%2F%2Fdeveloper.android.com%2Fcourses%2Fpathways%2Fandroid-basics-compose-unit-6-pathway-2%23codelab-https%3A%2F%2Fdeveloper.android.com%2Fcodelabs%2Fbasic-android-kotlin-compose-practice-bus-schedule-app#2) 

### deal with data layer
1. 设计实体类
2. 设计 Dao 接口
3. 创建 database
4. 为 database 这个数据源创建 repository

### deal with Dependency injection
1. 创建 container (很多个repository)
2. 创建 application (主要是把 context 传给 container)
3. 在 android manifest 里 注册 application

### deal with viewModel
从 repository 获取数据

### more complex data
考虑下面这种情况：
我们正在构建一个聊天机器人，每一个用户都有属于自己的聊天记录。那么我们要如何存储用户的聊天记录呢？
你可能会这么想：
```kotlin
data class User {
    val id: Int,
    val name: String,
    val password: String,
    val message: Message
}
```

但是 message 这个自定义类是存不进数据库中的，那我们要怎么解决这个问题呢？
可以共用一个主键 id, 令 id 同时为 User 和 Message 的主键

```kotlin
data class Message {
    val id: Int // same as User
    val history: List<String>
}
```

<++>
```kotlin
@Database(
    entities = [Message::class, User::class, Config::class],
    version = 6,
    exportSchema = false
)
```


