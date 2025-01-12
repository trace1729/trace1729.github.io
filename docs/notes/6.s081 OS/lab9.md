### File System

#### 8.1

some challenge for the file system

- data structrue to represnt file and directory
- handle crash 
- concurrency
- fast I/O

    | 七层模型        | 描述                                           |
    |-----------------|------------------------------------------------|
    | File Descriptor | 抽象Unix系统资源，比如 pipe, files, devices 等 |
    | Pathname        | 路径查找                                       |
    | Directory       | 一种特殊的文件                                 |
    | Inode           | 抽象文件                                       |
    | Logging         | 允许高层将多个 update 合并到一个 commit        |
    | Buffer cache    | 缓存 block, 并且将对缓存的更改同步到 disk      |
    | Disk            | 从硬盘读取 block                               |

blocks(sectors)

The blocks size file system uses is usally a multiple of sector size disk uses. 

Xv6 把从磁盘读取到的数据存放在 struct buf 里。(might be out of sync)

文件系统必须规划好在哪里存放数据。为此，文件系统将硬盘分成了几部分.

| 扇区号       | 描述                                          |
|--------------|-----------------------------------------------|
| Block 0      | 不使用                                        |
| Block 1      | superblock, stores metadata about file system |
| Block 2 - XX | Hold Log                                      |
| After log    | inodes                                        |
| After inodes | bitmap blocks tracking which block are in use |
| After        | data block                                    |

**buffer cache** 
 
1. 同步更改
2. 缓存最常访问快 (LRU)

`bread` and `bwrite` 

bread(dev, blockno) read data from disk to block. It calls bget search the doubled linkedlist for cached data. If not found, will recycle a not-used block.

bwrite write data in block to disk

`brelse` put the used buffer to the head of the doubled linkedlist.

**Logging Layer** 

crash recovery. use Log to make the process atomic 

在把内容写入磁盘前，先将所有 **磁盘写入的描述信息** 写入硬盘。
这样一来，如果是Log还没有写入完成时，系统崩溃。重启后，系统会忽视这个不全的日志信息。
如果是写入磁盘过程中发生崩溃，那么系统会根据日志文件重新操作一遍。

**Log design** 

Group commit. squash multiple operation into one commits to save disk access time

由于 Log 的设计导致所有的 系统调用一次向磁盘写入的内容不能超过 分配给 Log 的缓存空间
`write` 系统调用就必须将对大文件的写入拆分成多个 operation.

**code: Loging** 

`begin_op` 等待文件系统不再进行 `commit` ，且有空余的 Log 空间。

`log_write` 将要更改的扇区号写入内存, 并且对这个扇区的计数器加一。考虑到我们可能对多次对相同的扇区进行写入，增加了一个 `absorption` 机制, 就是循环遍历 log 数组，看一下之前是否已经保存了目前想要更改的扇区号。

`end_op` 提交更改。

**block allocator** 

balloc and bfree

**Inode layer** 

两种 inode.
- 储存磁盘数据的数据结构，文件大小、类型、以及储存的位置
- 储存内存中的数据结构，磁盘信息+操作系统附加上的额外信息

**dinode** 

    struct dinode {
      short type;           // File type
      short major;          // Major device number (T_DEVICE only)
      short minor;          // Minor device number (T_DEVICE only)
      short nlink;          // Number of links to inode in file system
      uint size;            // Size of file (bytes)
      uint addrs[NDIRECT+1];   // Data block addresses
    };

- The *type* field distin-guishes between files, directories, and special files (devices). A type of zero indicates that an on-disk inode is free. 
- The *nlink* field counts the number of directory entries that refer to this inode, in order to recognize when the on-disk inode and its data blocks should be freed.
- The *size* field records the number of bytes of content in the file. 
- The *addrs* array records the block numbers of the disk blocks holding the file’s content.


`itable` stores active inodes

**inode** is a in-memory copy of `dinode` 

- `iget` `iput` function modifies the ref count of i `inode` 



Invariants

- `itable.lock` protests a inode is present in itable only once and `ref` is only modified by one process
- `sleeplock` ensures exclusive access to inode's fields.
- `ref` maintain inode in itable when ref != 0  (count c pointers)
- `nlink` won't free a inode when nlink != 0 (count directory reference)

**code Inodes** 
Call `ialloc` to allocat a new inode. ialloc loops over the inode structures, looking for one that is
marked free (type == 0). Once found, it calls `iget` to get the corresponding entry from `itable`

`ilock` :Before reading the metadata from the file, we must call `ilock` . 

`iput` : decrement the referecnt pointer. If the `ref`  and `nlink` is  both less that 1, it calls `itrunk` to remove the data.


**Inode content (data)** 

dinode 储存数据的结构：

数据是分段存储的，一个数据段的大小是 1024 字节。 dinode 将每一段的起始地址存放在数组 `addr` 中。  
数据段分为两类，12个直接访问段(NDIRECT)和256个间接访问段(NINDIRECT)。addr[1~12] 存放的是直接访问段的其实地址，addr[13] 存放的是间接访问段的起始地址。

`bmap` 为 inode 获取某一个数据段的信息。(必要时调用 `balloc` 分配空间)


**Code: directory layer** 

目录是特殊的inode，它由许多个 directory entry 构成， 每一个entry 都是 `struct dirent` 

`dirlookup` 
`dirlink` 

**Code: Path names** 

involves a succession of calls to `dirlookup` 

**File Descriptor Layer**

every open file is `struct file`, which is wrapper around either `PIPE` or `INODE` or `DEVICE` . 

All the open files are kept in the global open files `ftable` 

`filealloc` 计数器置1

`filedup` 计数器+1

`fileclose` 计数器-1, 如果调到0，释放资源

`filestat` 把inode的信息传到 用户地址空间

`fileread` 

`filewrite` 

**Code System calls** 

`sys_link` 

creat new name for existing inodes.

`create` 

create new name for new inodes.

### Lab

#### Big File

实现一个二级 buffer. 不难, 就是要注意对 buffer 的内容进行更改后，要将改动写入 log.
然后 bread 和 brelse 成对出现。bread 一个 block, 要 brelse 后才能 bread 下一个 buffer.

#### Symbolic links

1. 怎样创造一个合法的 symbolic links. 

naive thought: use namei find the inode corresponding to the path, using ialloc to allocate a new inode
for symbolic link.

- we already have `create` function to create a new inode.

error cases:
    1. src do not exists
    2. target is not vaild
    3. src is directory or a symblic link

Q: inode 本身自己没有办法 储存偏移量，那我要把字符串放在哪里呢

A: inode 不需要储存偏移量，它只写入一次数据呀。

Q: 什么时候 iput 和 iunlock. iput 是什么意思。

- iput: 当有创建一个新的指针指向一个inode 时，inode 的 refcount 会自增；当这个指针不再被使用的时候，就需要调用 iput

- iunlock: 是用来维护 inode 的不变量的。再需要更改的 inode 的内容时，需要加锁。不再更改就释放。

- 通常 iput 和 iunlock 是一起使用的，于是就有了 iunlockput

Q: 为什么 create 时，不需要释放锁；

A: 因为 create 是个 static 函数，只在 sys_file.c 内部使用，调用 create 的 函数负责释放锁。

Q: 为什么 brelse 在 bmap 时，可以紧接着放在第一个 bread 之后，而在 itrunk 中，就会出现 `free free block` 的错误呢？

A: 因为 `brelse` 会递减 `bread` 获取的 block 的 refcnt。而 bfree 会回收 ref count 为 0 的 block。在 `bmap` 函数实现中，没有调用 `bfree` 函数, 所以不会出现提前回收(refcnt == 0)的情况，而在 itrunk 中，`ip->addr[NDIRECT + 1]` 所指向的block可能在执行外层的 `bfree` 之前，就已经被内层循环的 `bfree` 回收了。最后再次执行 `bfree(ip->addr[NDIRECT + 1])` 就出错了。


bget 使用了两把锁

- bcache lock
    保护 bache 的链表结构和节点信息不发生 race condition; 

- block lock
    保证只有一个进程在对 block cache 里的内容进行修改。这也意味着，进程对 block cache 的修改被 serilzie 了。可能会影响性能。
