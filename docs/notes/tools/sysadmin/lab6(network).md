# network 进阶版 (包含 nginx)

- **Question 1a:** What command did you use to display the networked services?

    netstat

- **Question 1b:** Paste the output of the command.

```
    Active Internet connections (only servers)
    Proto Recv-Q Send-Q Local Address           Foreign Address         State      
    tcp        0      0 localhost:domain        0.0.0.0:*               LISTEN     
    tcp        0      0 0.0.0.0:ssh             0.0.0.0:*               LISTEN     
    tcp        0      0 localhost:3000          0.0.0.0:*               LISTEN     
    tcp        0      0 0.0.0.0:8096            0.0.0.0:*               LISTEN     
    tcp        0      0 localhost:33060         0.0.0.0:*               LISTEN     
    tcp        0      0 0.0.0.0:5000            0.0.0.0:*               LISTEN     
    tcp        0      0 localhost:mysql         0.0.0.0:*               LISTEN     
    tcp        0      0 localhost:42063         0.0.0.0:*               LISTEN     
    tcp        0      0 0.0.0.0:http            0.0.0.0:*               LISTEN     
    tcp6       0      0 [::]:ssh                [::]:*                  LISTEN     
    tcp6       0      0 [::]:5244               [::]:*                  LISTEN     
    tcp6       0      0 localhost:42063         [::]:*                  LISTEN     
    tcp6       0      0 [::]:http               [::]:*                  LISTEN     
    udp        0      0 0.0.0.0:43741           0.0.0.0:*                          
    udp        0      0 0.0.0.0:1900            0.0.0.0:*                          
    udp        0      0 localhost:domain        0.0.0.0:*                          
    udp        0      0 iZuf64e9ug9p2r9x:bootpc 0.0.0.0:*                          
    udp        0      0 iZuf64e9ug9p2r9xd:55448 0.0.0.0:*                          
    udp        0      0 0.0.0.0:7359            0.0.0.0:*                          
    udp        0      0 localhost:323           0.0.0.0:*                          
    udp        0      0 localhost:58039         0.0.0.0:*                          
    udp6       0      0 localhost:323           [::]:*                             
    raw6       0      0 [::]:ipv6-icmp          [::]:*                  7          
    Active UNIX domain sockets (only servers)
    Proto RefCnt Flags       Type       State         I-Node   Path
    unix  2      [ ACC ]     STREAM     LISTENING     18887    /run/uuidd/request
    unix  2      [ ACC ]     STREAM     LISTENING     11226310 /run/systemd/userdb/io.systemd.DynamicUser
    unix  2      [ ACC ]     STREAM     LISTENING     26241    /usr/local/cloudmonitor/local_data/argus.sock
    unix  2      [ ACC ]     SEQPACKET  LISTENING     13386    /run/udev/control
    unix  2      [ ACC ]     STREAM     LISTENING     13371    /run/systemd/fsck.progress
    unix  2      [ ACC ]     STREAM     LISTENING     13381    /run/systemd/journal/stdout
    unix  2      [ ACC ]     STREAM     LISTENING     98918    /run/user/1001/systemd/private
    unix  2      [ ACC ]     STREAM     LISTENING     98923    /run/user/1001/bus
    unix  2      [ ACC ]     STREAM     LISTENING     98924    /run/user/1001/gnupg/S.dirmngr
    unix  2      [ ACC ]     STREAM     LISTENING     98925    /run/user/1001/gnupg/S.gpg-agent.browser
    unix  2      [ ACC ]     STREAM     LISTENING     98926    /run/user/1001/gnupg/S.gpg-agent.extra
    unix  2      [ ACC ]     STREAM     LISTENING     98927    /run/user/1001/gnupg/S.gpg-agent.ssh
    unix  2      [ ACC ]     STREAM     LISTENING     98928    /run/user/1001/gnupg/S.gpg-agent
    unix  2      [ ACC ]     STREAM     LISTENING     11226912 /run/systemd/journal/io.systemd.journal
    unix  2      [ ACC ]     STREAM     LISTENING     98929    /run/user/1001/pk-debconf-socket
    unix  2      [ ACC ]     STREAM     LISTENING     11216897 /run/containerd/containerd.sock.ttrpc
    unix  2      [ ACC ]     STREAM     LISTENING     11227920 /tmp/dotnet-diagnostic-1223391-511743523-socket
    unix  2      [ ACC ]     STREAM     LISTENING     11216902 /run/containerd/containerd.sock
    unix  2      [ ACC ]     STREAM     LISTENING     11241197 /var/run/docker/metrics.sock
    unix  2      [ ACC ]     STREAM     LISTENING     11243004 /var/run/docker/libnetwork/3fdc8a1ceef3.sock
    unix  2      [ ACC ]     STREAM     LISTENING     26685    /tmp/.s.PGSQL.42063
    unix  2      [ ACC ]     STREAM     LISTENING     11253192 /var/run/mysqld/mysqlx.sock
    unix  2      [ ACC ]     STREAM     LISTENING     11253194 /var/run/mysqld/mysqld.sock
    unix  2      [ ACC ]     STREAM     LISTENING     6848300  /tmp/aliyun_assist_service.sock
    unix  2      [ ACC ]     STREAM     LISTENING     26240    /tmp/argus.sock
    unix  2      [ ACC ]     STREAM     LISTENING     11247111 /var/run/openvswitch/db.sock
    unix  2      [ ACC ]     STREAM     LISTENING     11247112 /var/run/openvswitch/ovsdb-server.1228681.ctl
    unix  2      [ ACC ]     STREAM     LISTENING     11226308 /run/systemd/private
    unix  2      [ ACC ]     STREAM     LISTENING     18883    /run/dbus/system_bus_socket
    unix  2      [ ACC ]     STREAM     LISTENING     11247265 /var/run/openvswitch/ovs-vswitchd.1228731.ctl
    unix  2      [ ACC ]     STREAM     LISTENING     18885    /run/docker.sock
```

- **Question 1c:** Choose one service from the output and describe what it does.

    ssh, 远程链接

Q: Why is this the case? What DNS server are requests currently being sent to if @localhost is not specified in the command?
A: `dig www.baidu.com @localhost` 指定了在本地的 DNS 服务器查询 `www.baidu.com` 相关的记录，但是这个时候 本地的 DNS 服务器是处于关闭状态的。


- **Question 2a:** What is the systemctl command to show whether bind9 is running or not?

    `systemctl status` 
  
- **Question 2b:** Why does the dig command (dig ocf.berkeley.edu) work if @localhost is not present at the end (if bind9 is not started) but times out when @localhost is added?
  
A: `dig www.baidu.com @localhost` 指定了在本地的 DNS 服务器查询 `www.baidu.com` 相关的记录，但是这个时候 本地的 DNS 服务器是处于关闭状态的。

- **Question 2c:** What additional entries did you add to your DNS server config (the db.example.com file)?

    test1 IN CNAME test

- **Question 2d:** What commands did you use to make requests to the local DNS server for your additional entries?
    
    dig

### nginx (engine x) 文档

**Beginners guide** 

1. How start, stop and reload
2. explains the structure of the configruation file 
3. how to set up nginx to serve out static content
4. how to configure nginx as a proxy server
5. how to connect it with a FastCGI application

nginx 的 配置文件由两种 `directive` 构成

- `simple directive` 由名字和参数构成，中间由空格分开，结尾有分号
- `block directive` 构成与 `simple directive` 类似，但是以一对 `{}` 结尾，没有分号。在 括号内部可以定义其他的 `directive` 

*最外层的 directive* 叫作 main directive, 比如 `event` `http`

如何设置反向代理？

在 `nginx.conf` 的 http context 下，加入 server 的配置语句即可。`server` 的写法可参考 `sites-enable/myblog.trace1729.top` 

如何设置 SSL 证书？

首先，我们需要去阿里云控制台为我们的二级域名注册一个ssl证书 [ssl证书注册平台](https://yundunnext.console.aliyun.com/?spm=a2c4g.11186623.0.0.4b707216EsBlRl&p=cas#/certExtend/free/cn-hangzhou) 。(只需要填写二级域名和联系方式即可，其余默认设置)

审核通过后，下载 ssl 证书 并上传到服务器 (/etc/nginx/cert/)。(.key 和 .pem 文件)

在 `nginx.conf` 添加如下配置

    server {
	    server_name cloud.trace1729.top;
		rewrite ^(.*)$  https://$host$1 permanent; # 重定向到 https
    }
    
	server {
	    listen 443 ssl;
	    server_name cloud.trace1729.top; # 填写注册的域名
	    ssl_certificate cert/cloud.trace1729.top.pem; # 证书名称
	    ssl_certificate_key cert/cloud.trace1729.top.key; # 证书密钥
	    ssl_session_timeout 5m;
	    ssl_ciphers ECDHE-RSA-AES128-GCM-SHA256:ECDHE:ECDH:AES:HIGH:!NULL:!aNULL:!MD5:!ADH:!RC4;
	    ssl_protocols TLSv1.1 TLSv1.2 TLSv1.3;
	    ssl_prefer_server_ciphers on;

	    location / {
		proxy_pass http://localhost:5244;
		proxy_set_header Host $host;
		proxy_set_header X-Real-IP $remote_addr;
	    }
	  
	}

**haproxy** 配置负载均衡

1. 刷新页面多次，有什么规律吗？
按照 1, 2, 3, 4, 5 的顺序改变
2. 负载均衡的算法是什么 round-robin
3. 你加的配置是什么?
```bash
global
    maxconn 50000
    log /dev/log local0
    user haproxy
    group haproxy
    stats socket /run/haproxy/admin.sock user haproxy group haproxy mode 660 level admin
    cpu-map auto:1/1-4 0-3
    ssl-default-bind-ciphers ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256
    ssl-default-bind-options ssl-min-ver TLSv1.2 no-tls-tickets



defaults
    timeout connect 10s
    timeout client 30s
    timeout server 30s
    log global
    mode http
    option httplog
    maxconn 3000


listen stats
  bind    0.0.0.0:7001
  mode    http
  stats   enable
  stats   hide-version
  stats   uri /stats

frontend web.trace1729.top
	bind 0.0.0.0:7000
    default_backend web_servers


backend web_servers
    balance roundrobin
    cookie SERVERUSED insert indirect nocache
    default-server check maxconn 20
    server server1 0.0.0.0:8082 cookie server1
    server server2 0.0.0.0:8081 cookie server2
    server server3 0.0.0.0:8082 cookie server3
    server server4 0.0.0.0:8083 cookie server4
    server server5 0.0.0.0:8084 cookie server5

```

不知为何，这里的 ip 地址一定要写成 0.0.0.0 才能成功。
我很好奇 0.0.0.0, localhost, 服务器公网地址, 127.0.0.1 这些地址的区别。 

总结一下配置要点
首先 frontend 接受用户的请求，让后将请求转发给 backend 的服务器。 backend 更具声明的调度算法选择服务器。再把服务器的返回结果发给 frontend

4. Total change, green
5. red
6. 503 service unavaliable
