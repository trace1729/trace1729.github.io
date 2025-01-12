## lec 5
## Fragment

Why fragment
1. reuse 
2. reduce redundant

Lifecycle
1. tied to host activity

FragmentManager

FragmentTransactions
    - creating
    - launching
    - caching

group transaction

```
val fM = sFM;
fM.beginT
    .add(.., ..)
    .commit()
```

```mermaid
graph TD
B[F B] --> |setFR| F[FM]
F -->|request| A[F A]
A --> |setFRL| F

```

## Navigation
- Botton Navigation View
- TopBar
- 

