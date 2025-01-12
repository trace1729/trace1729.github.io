## Learn http
- privacy
- integrity
- indentification

## About Deployment

## retrofit

### dependency

version for `org.jetbrains.kotlin.plugin.serialization` might leads to error,
need some change based on project

```gradle
id 'org.jetbrains.kotlin.plugin.serialization' version '1.7.10'


// Retrofit 
implementation "com.squareup.retrofit2:retrofit:2.9.0"
// Retrofit with Scalar Converter
implementation "com.squareup.retrofit2:converter-scalars:2.9.0"

// Kotlin serialization 
implementation "org.jetbrains.kotlinx:kotlinx-serialization-json:1.4.0"

// Retrofit with Kotlin serialization Converter  convert json to kotlin objects
implementation "com.jakewharton.retrofit:retrofit2-kotlinx-serialization-converter:0.8.0"

// OKHTTP3
implementation 'com.squareup.okhttp3:okhttp:4.10.0'
implementation 'com.squareup.okio:okio:3.2.0'
```

### Android permissions

in `<activity>` tag add `<uses-permission android:name="android.permission.INTERNET" />` 
in `<activity>` tag add `android:usesCleartextTraffic="true"` 


### How to use retrofit


1. creat `dataclass` with `@Serializable`

```kotlin
@Serializable
data class MarsPhoto(
val id: String,
@SerialName(value = "img_src")
val imgSrc: String
)
```

2. creat network request api

```kotlin
interface SongApiService {
@GET("music/{name}")
suspend fun getSongInfo(@Path("name") name: String): List<SongInfo>

@GET("music/id/{rid}")
suspend fun getSongUrl(@Path("rid") rid: Int): MusicUrl
}
```

3. register in AppContainer

- initilize retrofit objects
    ```kotlin
    private val retrofit: Retrofit = Retrofit.Builder()
    .addConverterFactory(Json.asConverterFactory("application/json".toMediaType()))
    .baseUrl(SONG_URL)
    .build()
    ```

- creat retrofit service based on api you create
    ```kotlin
    private val retrofitService by lazy {
    retrofit.create(SongApiService::class.java)
    }

    ```

4. set up repositorty
```
override val songRepository: SongRepository by lazy {
SongRepository(retrofitService)
}
    ```



5. set up viewModel
