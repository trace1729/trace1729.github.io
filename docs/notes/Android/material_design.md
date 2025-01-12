## material_design

material design aims to provide a design standard for all android apps.
It not only reduece the time developers spending in Ui design, but also
provides users a consistent experience using different apps

it mainly has five parts

### color
color spread in four places
TopAppBar primary
App: background
item: surface (content)
icon: secondary

- define color in `ui/theme/color.kt`
- set up color in `ui/theme/Theme.kt` 

code sample

```kotlin
// in color 
//Light Theme
val Grey50 = Color(0xFFF8F9FA)
...

//Dark Theme
val White = Color(0xFFFFFFFF)
...

// in theme

private val DarkColorPalette = darkColors(
    background = Cyan900,
    surface = Cyan700,
    onSurface = Grey100,
    primary = White,
    onPrimary = Grey100,
    secondary = Grey900
)
```

### typo
- new a `Android resource directory` named `font` in `res` foldr
- put downloaded font in `font` dir
- set up font in `ui/theme/typo.kt` 

1. initilize Fonts
```kotlin
// Set of Material typography styles to start with
val AbrilFatface = FontFamily(
    Font(R.font.abril_fatface_regular)
)

val Montserrat = FontFamily(
    Font(R.font.montserrat_regular),
    Font(R.font.montserrat_bold, FontWeight.Bold)
)
```

2. set up for font size range from h1 - h6 & body

```kotlin
val Typography = Typography(
    h1 = TextStyle(
        fontFamily = AbrilFatface,
        fontWeight = FontWeight.Normal,
        fontSize = 30.sp
    ),
    h2 = TextStyle(
        fontFamily = Montserrat,
        fontWeight = FontWeight.Bold,
        fontSize = 20.sp
    ),
    h3 = TextStyle(
        fontFamily = Montserrat,
        fontWeight = FontWeight.Bold,
        fontSize = 14.sp
    ),
    body1 = TextStyle(
        fontFamily = Montserrat,
        fontWeight = FontWeight.Normal,
        fontSize = 14.sp
    )

)
```

<++>

### shape

### some great functions
1. `modifier.weight()` specify the propotion of current component
> some question, where did this component align to given allocated space
2. `modifier.padding(horizonal = , vertical = )` 这指定了 `modifier ` 修饰的对象与外部对象的 `padding` 
3. 

