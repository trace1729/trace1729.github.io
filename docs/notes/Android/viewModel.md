## viewModel
0. dependency

```gradle
ext {
        compose_version = '1.3.0'
        compose_compiler_version = '1.3.0'
        lifecycle_version = '2.5.1'
    }


implementation "androidx.lifecycle:lifecycle-viewmodel-compose:$lifecycle_version"
```

<++>

1. create uiState.
> 什么属性要被放进 uiState 里呢, 原本在Ui界面，类型为`mutableState` 的变量都应该放入uiState 这个类中

> 最好给每一个属性赋初始值，在viewModel中用的上
2. create viewModel

每一个 `viewModel` 应该有一个 `uiStata` 用来反映 Ui 当前所处的状态.

sample code

```java
// why mutable: mutable means we can change value for current stateflow
    // when _uiState changes, schedule a recomposition
    private var _uiState = MutableStateFlow(DessertUiState())

    // the uiState we expose to user is immutable
    val uiState: StateFlow<DessertUiState> = _uiState.asStateFlow()

    private var revenue by mutableStateOf(0)

    var dessertSold by mutableStateOf(0)
            private set

    var currentDessert by mutableStateOf(dessertList[0])
```


3. 在 Ui layer 中，初始化 `viewModel`

- 可以直接在函数的参数处，创建`viewModel` 

sample code

```java
@Composable
private fun DessertClickerApp(
    viewModel:DessertViewModel = DessertViewModel()
) {
    val uiState = viewModel.uiState.collectAsState()
    // if you use `by`, then you do not need `uiState.value` to get value, 
    // it auto - overloads get method 
//    val uiState by viewModel.uiState.collectAsState()
// ... ... 
}
```




