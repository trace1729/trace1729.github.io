## 遇到的问题

1. 如何根据系统主题更换应用主题
- `isSysteminDarkTheme` <++>

2. navigation with arguments

3. 访问网络请求成功，但是ui 获取不了访问的数据.

原因：由于网络请求是在携程中进行，渲染Ui则是在主线程进行，又因为网络请求比较缓慢，这就导致应用在获取到
网络请求所返回的数据前，就已经把默认值给传递下去，导致解析异常。

解决方案：为Ui设计一些状态，比如 

```kotlin
enum class STATUS {
    SUCCESS,
    LOADING,
    FAILURE
}


fun getUrl() {
        viewModelScope.launch {
            playUiState =  try {
                val url = songRepository.getSongUrl(songId).url
                PlayUiState(url, STATUS.SUCCESS)
            } catch (e: IOException) {
                Log.e("Play", "io exception")
                PlayUiState(status = STATUS.FAILURE)
            } catch (e: HttpException) {
                PlayUiState(status = STATUS.FAILURE)
            }
        }
    }
```

而在 UI layer 中， 我们根据 Ui 所处的状态 来 动态调整 界面的显示效果

```kotlin
 when (uiState.status) {
        STATUS.SUCCESS -> Player(url = uiState.url)
        else -> Loading()
    }
```

这样一来，只有当 网路请求结束后，Ui layer 才会将 url 传递给播放器。

4. json 解析异常. 

问题：
网络请求返回json数据中 year 字段为空，会导致 kotlin serialization 解析异常

原因：
schema 里 year 的字段为 Int, kotlin.serialization 无法将 空字符串解析为 Int 

解决方案：
将 year 字段 的类型调整为 String

5. 获取数据库数据失败

问题：在从 dataStore 获取到数据之前，uid的值就传递给了数据库

解决方案
将 从 dataStore 获取数据 和 从 数据库获取数据 分别放在 两段 viewModelScope 中 即可

```kotlin
fun closeDrawer() = _uiState.update { it.copy(drawerValue = DrawerValue.Closed) }
    private fun openDrawer() = _uiState.update { it.copy(drawerValue = DrawerValue.Open) }
    fun onDrawerStateChange () {
        if (uiState.value.drawerValue == DrawerValue.Closed) {
            openDrawer()
        } else {
            closeDrawer()
        }
    }
```




