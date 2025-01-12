## Activity and intent

## intents

- Explict intents
calls antther `oncreate()` method of anther activity

To transition to a new activity, we first create an intent with
the following code
```javascript
var intent = Intent(this, TargetActivity::class.java)

```
> The `.java` is some sort of convention, though it might seem wierd.
To launch an activity with the given intent, we write
```kotlin
 startActivity(intent)
```

To close
```
finish()
```

## send data

include info within intent. we write 
```javascript
putExtra(key, value)
```

This stores everythings in a bundle

## receive data

```javascript
// eateryName = "Okenshields"
var eateryName = getIntent().extras?.getString("EATERY_NAME")
```

## send back info

In the above content, we have implemented function like 
launching a new activity, 
sending info from current acti to target acti.
And now, we wonder how to send data back to a launched acti
Introduction a new method

```javascript
// In MainActivity.kt
registerForActivityResult(ActivityResultContract, ActivityResultCallback)
```
```kotlin
private lateinit var intentLauncher: ActivityResultLauncher<Intent>
// ...
intentLauncher = registerForActivityResult(
   ActivityResultContracts.StartActivityForResult()
) {
   result ->
   if (result.resultCode == SOME_UNIQUE_INTEGER) {
       val hi = result.data?.extras?.get("hi")
       println("MainMain")
       binding.textviewId.text = hi as String
    }
   }
  // ...
   intentLauncher.launch(intent) // use intentLauncher
   // ...
   
 companion object {
        // Can be referenced both within the MainActivity and other
        // Activities (e.g. your TargetActivity)
        const val SOME_UNIQUE_INTEGER = 1
    
```

we mark the return value of above code as `intentLauncher`
and use `intentLauncher.launch()` to load intent, instead of 
`startActivity`.

In targetActivity 

we create a new intent, load info, **and** setResult
```java
override fun onBackPressed() {
     val intent = Intent()
     println("asasasa")
     intent.putExtra("hi", "hi")
     setResult(SOME_UNIQUE_INTEGER, intent)
     super.onBackPressed()
}
// Interger 作为resultCode, 可以利用它来标记多种功能 
```
## implicit intent

implicit means we do not call `onCreate` method.
It is a feature that allows us to communicate among other apps



