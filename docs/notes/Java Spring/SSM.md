### Spring 基础

熟悉了 spring bean 用法
 - 使用 xml 配置
 - 使用 注解 配置


了解 Mybatis 是如何封装 driver.connection 对数据库进行操作的。

了解 Mybatis 是如何与 Spring 框架交互的。

**Mybatis 事务管理** 
- 原子性
- 一致性
- 隔离性 详细讨论
- 持久性

**隔离性** 

> 可能有许多事务会同时处理相同的数据，因此每个事务都应该与其他事务隔离开来，防止数据损坏

| 隔离级别 | 解释                                                             | 出现的问题 |
|----------|------------------------------------------------------------------|------------|
| 读未提交 | 在另一个事务还没提交的时候读取数据                               | 脏读       |
| 读已提交 | 在一个事务还在操作数据的时候更新数据                             | 虚读       |
| 可重复读 | 在一个事务对数据库进行操作时，禁止其他事务对数据库的 update 操作,(但是不禁止 insert) | 幻读       |
| 串行读取 |                                                                  |            |


总结: 

首先在 MainConfiguration 中 配置 dataSoure。javaBean 根据 参数的类型自动将 dataSoure 注入到
`transactionManager` 和 `sqlSessionFactory` 中。后一个是用于操作数据库，前一个用于对数据库的事务处理。

MainConfigraion 的注解含意分别为
1. `Configuration`: 声明是配置文件
2. `ComponentScan`: 扫描其他 `Component`, 为它们提供依赖注入。比如 Mapper
3. `MapperScan`: 顾名思义
4. `Transactional`: 开启事务功能

在 主函数中。
利用 `AnnotationConfigApplicationContext` 生成一个 `ApplicationContext` 对象，利用这个对象和 JavaBean 进行交流。
做处理。


### Spring MVC

DispatcherServlet --> HanderMapping --> HanderExecutionChain --> HanderInterceptor --> HanderAdaper
HanderAdapter --> (Model and View) ViewResolver --> DispatcherServlet

基本上我们只需要配置一下 webconfigruation, 补齐 controller 实现就可以。

其余的重点：
重定向 和 请求转发 (重定向是转发到 controller 里配置的另一个 url 不是静态资源的文件名)
Session 作用域 
拦截器
axios 异步处理

SVC 三层模型
   - controller 和 service 沟通
   - service 和 Mapper 沟通
   - Mapper 和 数据库沟通

### Spring Security

配置一下 Security Configuration，编写相应的 service 和 controller 即可。
需要注意的是 我们可以通过创建一个 passwordencoder (标示为 bean) 用来指定 Spring 对用户密码的加密方式。

404 错误
    - 可能没有在 controller 配置相应的 url
    - 在 controller 配置的 url 在末尾多了一个 /
    
302 错误
    - 没有在 `SecurityFilterChain` 放行静态资源。

403 错误
    - 没有提交 *csrf* token

defaultSuccessurl not working

将 remember-me 的 cookie 存放在 数据库中出错 

    Unsatisfied dependency expressed through method 'setFilterChains' parameter 0: Error creating bean with name 'filterChain' defined in com.example.config.SecurityConfiguration: Unsatisfied dependency expressed through method 'filterChain' parameter 1: Error creating bean with name 'tokenRepository' defined in com.example.config.DatabaseConfiguration: Initialization of DAO failed

实际上数据库已经创建完了，这是第二次创建，所以报错


### 项目实战， 图书管理系统

问题：配置了 Spring Security 后 并没有出现 登入界面。
- `SecurityInitializer` 没有继承 `AbstractSecurityWebApplicationInitializer`

问题：登入成功后进入不了主页
- 需要将 表单的 name 修改为 "当前项目的上下文:doLogin"

问题：登录后网页重定向失败
- 在两个 controller 对于同一个请求配置了不同的映射

问题：添加借阅信息的时候，post 请求失败，没有携带参数。

- 通过查阅资料，发现 firefox 可以获取 浏览器发送的 post 请求。查看后发现浏览器是有附带数据的。
那为什么后端没有获取到呢。原来是因为，后端 controller 接受浏览器发送的参数时，参数的名字要保持一致，它不是按照顺序来的。

问题：查询图书信息时，book_list_status(iterSet.index) 解析错误
- 一开始给 book_list_status 传的是 map.values(), 不支持随机访问，应该转化为 list。

问题: 增加图书的时候
when I send out the post request, the server give me the following output, what might be the problem
org.apache.ibatis.binding.BindingException: Parameter 'title' not found. Available parameters are [arg2, arg1, arg0,

- 接受多个参数的时候，需要使用 Param 注解来 注明传递的参数名称

问题：借阅者姓名显示不出来。
- 添加借阅信息时，将 bid 与 sid 写反，可以通过添加外键约束来避免。


