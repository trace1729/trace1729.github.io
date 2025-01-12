# Manjaro+Windows 双系统安装教程

> (可参考[archlinux 装机指南](https://arch-linux.osrc.com/rookie/desktop-env-and-app.html#_10-%E5%AE%89%E8%A3%85%E8%BE%93%E5%85%A5%E6%B3%95))

## 下载安装包

1. dowmload .iso from offical website [下载地址](https://manjaro.org/download/)
2. make installer with an empty storage and rufus
3. 更改BIOS
   - magicbook pro
	 1. Getting into the BIOS, changer HDD device
	 2. reboot
   - pavilon 14 plus
	 1. 开机界面按F10进入BIOS, 关闭安全启动
	 2. 重启，插入U盘，按F9, 选择 UEFI: xxxx 从u盘启动 
4. config, and restart
5. 如果想要将u盘回复成正常状态，可[参考](https://blog.csdn.net/qq_41882686/article/details/89365660)
6. 之后可以尝试使用 ventory, 这样就可以在一个 u 盘安装多个启动程序

## 安装后的基本配置

- 如果你是高分屏，可以在 settings -> System-settings -> Display and Monitor 里面设置缩放比例 (kde)
- 如果你是高分屏，你可能需要设置 grub 的缩放。
  - 首先在 grub 界面 (就是选择哪一个操作系统启动的界面) 按 `c` 进入 cmd 界面，输入
  `videoinfo` 查看屏幕支持的分辨率
  - 开机后在 `/etc/default/grub` 下添加 `GRUB_GFXMODE="640x480x32"`
  - `sudo grub-mkconfig -o /boot/grub/grub.cfg` 更新grub
- 配置 archlinuxcn 
  输入`sudo nano /etc/pacman.conf`
  将下面这个镜像添加在文件最下面
  ```text
  [archlinuxcn]
  SigLevel = Never
  Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
  ```
- 切换国内源  
  `sudo pacman-mirrors -c china`
- 安装 yay，aur 助手
  ```bash
  sudo pacman -Syu
  sudo pacman -S yay # 安装 AUR 助手
  ```  
- 安装 obs 用于录屏
- 安装常用软件，便于后续配置 neovim, lazygit, ranger, tmux，alacritty
- 安装浏览器
  - chromium 需要额外配置才可以进行同步 [ref](https://stackoverflow.com/questions/67459316/enabling-chromium-to-sync-with-google-account)
- 配置代理 (clash)
    * 检查终端代理是否正常
    * 检查浏览器代理是否正常
- 安装字体文件
- 给 github 添加 SSH-key
  - 设置 ssh 走 http 代理 [doc](https://docs.github.com/zh/authentication/connecting-to-github-with-ssh/using-ssh-agent-forwarding)
- 给常用软件导入配置文件 (dotfiles)
  - nvim 的配置依赖 npm, nodejs, yarn

> bonus 

- 可以在旧机器上开启 sshd, 方便两个机器之间互传文件
  - 确保两个机器在相同局域网下
  - 在旧机器上开启 `sudo systemctl enable sshd && sudo systemctl start sshd`
  - 通过 `ip addr` 查看 ip 地址
  - 在新机器上 通过 `ssh {username}@{ip}` 
- 将旧机器上 gnome 的配置导出到 新机器
- 可以使用 localsend 来进行不同设备间的文件传输

## 安装常用软件

### pacman

> summery: [输入法] fcxit5 [ASCII ART]: lolcat, figlet [图片壁纸]：variety feh flameshot
> [写作工具] obsdian emacs zotero
> [图像处理、视频剪辑] kdenlive
> [多屏协同] rustdesk scrcpy
> [邮件管理] thunderbird
> [RSS订阅] fluent-reader
> [podcast] vocal
> [wechat] wine-wechat-setup

fcitx5

1. 安装程序

	``` shell
	sudo pacman -S fcitx5-im # 输入法基础包组
	sudo pacman -S fcitx5-chinese-addons # 官方中文输入引擎
	sudo pacman -S fcitx5-anthy # 日文输入引擎
	sudo pacman -S fcitx5-pinyin-moegirl # 萌娘百科词库。二刺猿必备（archlinuxcn）
	sudo pacman -S fcitx5-material-color # 输入法主题
	```
	
2. 安装 rime-auto-deploy
3. 此外，我们还需要设置环境变量。通过 vim 编辑文件 /etc/environment

   ``` text
    GTK_IM_MODULE=fcitx
	QT_IM_MODULE=fcitx
	XMODIFIERS=@im=fcitx
	SDL_IM_MODULE=fcitx
	GLFW_IM_MODULE=ibus
   ```
4. 在 Fcitx 界面添加 Rime

![](https://image-trace.oss-cn-shanghai.aliyuncs.com/img/Screenshot%20from%202024-01-18%2019-04-50.png)

![](https://image-trace.oss-cn-shanghai.aliyuncs.com/img/Screenshot%20from%202024-01-18%2019-04-06.png)

emacs

删除插件目录，使用 `M-x install-selected-packages` 重新安装插件



### 常用的命令行工具

`sudo pacman -S ripgrep fd lsd zoxide fzf tldr`

### yay

> summery: linux_qq, wps-office, visual-studio-code-bin

```
yay -S wps-office-mui-zh-cn wps-office-mime-cn wps-office-cn wps-office-fonts ttf-ms-fonts  ttf-wps-fonts
yay -S wemeet-bin
yay -S baidunetdisk-bin
yay -S clash-for-windows-bin
yay -S netease-cloud-music-gtk-bin
yay -S xmind
```


vscode

启用同步功能，同步设置

<font color='red'> Tips </font> 

- 输入法脚本 [github](https://github.com/Mark24Code/rime-auto-deploy) 
- flameshot 无法获取截图 `yay -S xdg-desktop-portal-gnome-noprompt-git` 
- wpspdf 没有办法打开 `yay -S libtiff5` 
- pyright import 报错的话，退出重新进入试试。在 neovim 里创建一个文件，不关闭 neovim，而
- 使用 `e XX` 打开另一个 py 文件，引用刚刚创建的文件时，会失败
- wps 无法使用fcitx5 安装manjaro-asian-input-support-fcitx5 
