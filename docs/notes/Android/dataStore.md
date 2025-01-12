## dataStore

### dependencies
`implementation "androidx.datastore:datastore-preferences:1.0.0"` 

### setup repo 
1. create a new kotlin class called `xxxPreferenceRepository`, 
    this class takes one parameter `dataStore: DataStore<Preference>` 


2. list every element you want to save

```kotlin
val themeMode: Flow<String>
...
```

3. define saveXXX method

```kotlin
suspend fun saveThemePreference(themeMode: String){
        dataStore.edit { preferences ->
            preferences[THEME_MODE] = themeMode
        }
    }
```

4. put key for dataStore in companion object

```kotlin
 private companion object {
        val THEME_MODE = stringPreferencesKey("theme_mode")
        const val TAG = "UserPreferencesRepo"
    }
```

5. config dependency injection in application

```kotlin
// create A dataStore named SETTINGS 
private const val SETTINGS = "settings"
private val Context.dataStore: DataStore<Preferences> by preferencesDataStore(
    name = SETTINGS
)

class AudioApplication: Application(){

    lateinit var container: AppContainer
    lateinit var userPreferencesRepository: UserPreferencesRepository


    override fun onCreate() {
        super.onCreate()
        container = AppDataContainer(this)
        userPreferencesRepository = UserPreferencesRepository(dataStore)
    }
}

```



### setup viewModel

