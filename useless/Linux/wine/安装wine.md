# 安装wine

## 参考资料

1. 【ubuntu上安装wine】 https://www.sysgeek.cn/ubuntu-wine/
2. 【如何在ubuntu上安装wine】 https://zhuanlan.zhihu.com/p/645456382
3. 【从清华园安装wine】 https://mirrors.tuna.tsinghua.edu.cn/help/wine-builds/

Wine（也就是 [WineHQ](https://www.winehq.org/)）是一款 Windows 兼容层，能让你在类 Unix 操作系统（如 Linux）上直接运行 Windows 应用程序，而无需安装双系统或借助虚拟机。

> [!warning]
> 下面的安装教程来自网络，需要外网环境，如果需要安装国内源请看后面的内容
> 
> 还要注意，这里只是安装了wine，还没有完全配置好wine之前是不能用的。

## 1.1 准备工作

1。在安装 Wine 10 之前，先通过「终端」更新系统中的软件包：

```sh
sudo apt update  # 更新软件包列表
sudo apt upgrade # 升级软件包
```

2。接着，安装必要的依赖工具：

```sh
sudo apt install dirmngr ca-certificates curl software-properties-common apt-transport-https
```

3。启用 32 位系统架构支持，增强对游戏和应用程序的兼容性：

```sh
sudo dpkg --add-architecture i386
```

## 1.2 添加 WineHQ 官方仓库

1首先，导入 WineHQ 的 GPG 密钥：

```sh
curl -s https://dl.winehq.org/wine-builds/winehq.key | sudo gpg --dearmor | sudo tee /usr/share/keyrings/winehq.gpg > /dev/null
```

2然后，添加 WineHQ 官方仓库：

```sh
echo deb [signed-by=/usr/share/keyrings/winehq.gpg] http://dl.winehq.org/wine-builds/ubuntu/ $(lsb_release -cs) main | sudo tee /etc/apt/sources.list.d/winehq.list
```

在完成后，更新软件包信息和安装 Wine 的稳定版本软件包。

```text
sudo apt install --install-recommends winehq-stable
```

如果你现有开发版本或暂存版本，相应地使用 `winehq-devel` 或 `winehq-staging` 。

# 从清华园安装wine

首先启用 32 位架构

~~~sh
sudo dpkg --add-architecture i386
~~~

之后信任来自 https://dl.winehq.org/ 的公钥

```sh
sudo wget -nc -O /usr/share/keyrings/winehq-archive.key https://dl.winehq.org/wine-builds/winehq.key
```

新增 `/etc/apt/sources.list.d/winehq.list`，内容为

```sh
deb [arch=amd64,i386 signed-by=/usr/share/keyrings/winehq-archive.key] https://mirrors.tuna.tsinghua.edu.cn/wine-builds/ubuntu/ noble main
```

通过以下命令安装 winehq

```sh
sudo apt update
sudo apt install --install-recommends winehq-stable
```

