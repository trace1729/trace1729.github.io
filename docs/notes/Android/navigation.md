## How to use navagation

1. add dependency
`implementation "androidx.navigation:navigation-compose:2.5.3"` 

2. using enum or object to distinguish screen.

sample code

```kotlin
enum class LunchTrayScreens(@StringRes val title: Int) {
    START(title = R.string.start_order),
    ENTREE_MENU(title = R.string.choose_entree),
    SIDE_DISH_MENU(title = R.string.choose_side_dish),
    ACCOMPANIMENT_MENU(title = R.string.choose_accompaniment),
    CHECKOUT(title = R.string.order_summary),
}
```

<++>

3. build Up Navgation host `NavHost` 

`NavHost` is responsible for choose screen to display

It basically takes four arguments

- `modifier` 
- `navController` get it by `rememberNavController` 
- `startLocation` initial screen to display
- `content` compose function
    - the content is consisted of multiple `composable`, each of which is the screen to display
    - `composable` take `location` and `content` as its arguments

sample code

```java
 NavHost(
            navController = naviController,
            startDestination = LunchTrayScreens.START.name,
            modifier = Modifier.padding(innerPadding)
        ) {
            composable(LunchTrayScreens.START.name) {
                StartOrderScreen(onStartOrderButtonClicked = {
                    naviController.navigate(LunchTrayScreens.ENTREE_MENU.name)
                })
            }
            // ...
    }
```

4. build up TopAppbar

sample code

```kotlin
 TopAppBar(
        modifier = modifier,
        title = { Text(text = stringResource(id = currentScreens.title)) },
        navigationIcon = {
            if (canNavigateBack) {
                IconButton(onClick = navigateUp) {
                    Icon(
                        imageVector = Icons.Filled.ArrowBack,
                        contentDescription = stringResource(id = R.string.back_button)
                    )
                }
            }
        }
    )
```

In main activity
```kotlin
 val backStackEntry by naviController.currentBackStackEntryAsState()
    // TODO: Get the name of the current screen
    val currentScreen = LunchTrayScreens.valueOf(backStackEntry?.destination?.route  ?:
    LunchTrayScreens.START.name)
```


5. useful function

- popstack `navController.popBackStack(LunchTrayScreens.START.name, false)`
- 返回上一级目录 `navController.navigateUp()` 


6. Navigating With arguments

- 发送参数 `navController.navigate("${route}"/${id})`.
Note The the value of `id` is specified by you. (act as a `key` to get value)

- 接受参数 

**note the brackets** 
```kotlin
// 接收 一个参数
compose(route = ${route}"/{${id}}) 
// 接收多个参数
compose(route = ${route}"/{${id}}, arguments = listOf(navArgument(ItemDetailsDestination.itemIdArg) {
                type = NavType.IntType })) 
```
- 获取参数
1. using `viewModel` 

```kotlin
private val songId: Int = checkNotNull(savedStateHandle["id"])
```

2. using `navigation` 

```kotlin
composable("profile/{userId}") { backStackEntry ->
    Profile(navController, backStackEntry.arguments?.getString("userId"))
}
```




