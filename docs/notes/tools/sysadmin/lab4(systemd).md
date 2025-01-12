# Systemd

Q: what is a service
A service is a type of process known as a Daemon (守护进程)

Q: what is host, and what is client.
A: If running a vm on a real laptop, the real laptop is the host and the vm is the client

Q: What is the difference between `restart` and `reload` 
A:

在配置环境遇到的一些问题

```python
AttributeError: module 'virtualenv.create.via_global_ref.builtin.cpython.mac_os' has no attribute 'CPython2macOsArmFramework'
```

How can I solve it? 

原因是使用 apt 和 pip 分别安装了 virtualenv.
解决方案，全部卸载，再任意选一种方案安装。

Q: what is the command to crash the service
A: using curl command to send post request

```
curl --data '{"crash": true}' --header 'Content-Type: application/json' http://106.14.250.49:5000/crash
```

### systemd

systemd 管理着一系列的守护进程(daemon or services)，比如 sshd, networkd. 

**如何使用 systemd 管理一个自定义服务**

在 `/etc/systemd/system/` 下添加一个 `XXX.service` 的文件。
systemd 通过这个文件来管理服务。

文件一般遵循一下格式。每一个域的可选值和说明，请看文档

```
[Unit]
Description=
Requires=
After=

[Install]
WantedBy=multi-user.target

[Service]
ExecStart=
User=
```

### process

操作系统相关

可以看 [htop 详解](https://peteris.rocks/blog/htop/) 这个博客，对 Linux 下进程有很详细的分析。


