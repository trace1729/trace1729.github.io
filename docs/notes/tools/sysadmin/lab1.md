`tgz` 文件实际上是两种文件格式的组合, 有时这个文件格式也被写作 `tar.gz` . 
    - `tar` 是 tape archive 的缩写, 之前人们使用磁带做归档工作,这就有了 tar.
    - `tar` 本身只是将 多个文件合并成一个文件,并不能压缩.这就有了 `gzip` .

file --(tar)--> file.tar --(gzip)--> file.tar.gz
