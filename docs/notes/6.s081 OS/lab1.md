## primes
- How to stop program
    - -1 作为终结符
    - 注意在父进程 最后 加上 wait(0);
- when you are confused about the output, pint out the pid would be convenient

## find
先看ls的实现细节：
    - 首先根据参数个数判断输入是否合法
        - 若输入的参数个数为0 直接退出
        - 否则，分别对每一个参数 执行 ls 函数
 
ls 函数的实现细节
some struct and function api
- struct dirent 

    | name | type    | description       |
    |------|---------|-------------------|
    | inum | ushort  | number of files ? |
    | name | char [] | file names array  |

- struct stat

    | name  | type  | description                       |
    |-------|-------|-----------------------------------|
    | dev   | int   | file system disk divice           |
    | ino   | uint  | file poniters ponits to the array |
    | type  | short | type of a file                    |
    | nlink | short | number of links to the file       |
    | size  | size  | size of a file                    |

- system call close

    | arugments            | description                    |
    |----------------------|--------------------------------|
    | const char* pathname | the name of the file           |
    | int flag             | specify the way to open a file |

    | flag                           | des              |
    |--------------------------------|------------------|
    | O_RDONLY, O_WRONLY, or O_RDWR. | 只读，只写，读写 |

    | return Value | des               |
    |--------------|-------------------|
    | int fd       | file descripnator |

- fstat (file state)
    
    | arugments    | description                                             |
    |--------------|---------------------------------------------------------|
    | int fd       | file descripnator                                       |
    | struct stat* | the info retrived from file fd points to was saved here |


    | return Value | des       |
    |--------------|-----------|
    | status code  | 0 success, -1 failed |

- details about the ls
    - first we open the file according to the file name (string)
    , and we get fd
    - using fd, we call `fstat` ,to retrieve the metadata from it,
    - according to the file, we have the following operation
        - if it is a `T_FILE` we print it 
        - if it is a `T_DIR` we 
- persudo code for "find"

```code
takes two argument, 
    1. target directory
    2. find target
open target directory, iterate through the catalogue
    if it is a file, we compare it to file target
    if it is a direc, we do it recursively
```  
### problem
- how to iterate through a direc in unix
- what is `.`, `..` be represented for
- cannot open file, maybe file name wrongs
    - do not close the file descripnator, so new file cannot be open

## xargs 
### problem
- how can we know we are excecuting xargs command
- how can I get the arguments from the pipe 
    - we **do not need** to know, just read from standard input.
    the os provide us with abstraction using pipe.
 - how can pass char**  arg as the second  argument for exec, as we need to increase the number of arugments,
    instead of copy value, we just assign poniters
### How to implement
- is the second paramter == '-n'
    - yes,  then we store the specified maximum arguments 
    - no, we read all the input, replace \n -> ' ' 
  
