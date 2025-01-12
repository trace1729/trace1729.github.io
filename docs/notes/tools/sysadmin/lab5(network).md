# network

### 协议

**MAC**地址

MAC 地址是分配给一个网络接口的标识符, 它可以唯一确定一个接口，所以又被称为物理地址。

一个典型的 MAC 地址是 00:14:22:01:23:45, 注意前三字节是组织标识符，用来判断设备的制造商。

**IP地址** 

区分连接在互联网上不同设备的方法

**ARP** 
将 IP 地址解析为 MAC 地址的 一种协议。

**DNS** 

DNS 是一个将 32位IP地址映射到一个字符串的协议。
DNS 服务器数据以 `Resource Records` 的形式存储。`Resource Records` 包括以下字段

1. name
2. value
3. type
4. TTL

**TCP UDP** 

### 有用的命令

`hostname` 
展示本机的一些网络信息。
`ping` 
`traceout` 
`arp` 
`dig` 
`ip` 
`curl` 
`wget` 
`netstat` 
`tcpdump` 
`nc` 

### 练习

快问快答

1. HTTP uses TCP. 保证连接的稳定性，不能出差错。
2. paypal
3. 2^24 - 2
4. address record (storing a mapping between a domain name and a ip address)
    or NS record (the name server responsible for resoving the domian name).
    etc.
5. yes, because ping can send ICMP packet to the destination. If the packets failed to arrive, it states the connection may fail.
