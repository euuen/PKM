Docker必须要安装到Linux上才行。

> 于2025年6月编辑，因为技术迭代速度很快，注意时效性
## Arch系安装

```sh
sudo pacman -S docker
```

然后启动服务和把服务注册一下

```cpp
systemctl enable docker
systemctl start docker
```

## Ubuntu安装

这里以阿里云的服务器为例子吧。我真的福乐你啊，阿里云！

```c p p
apt-get install docker-ce docker-ce-cli containerd.io
```

然后启动服务和把服务注册一下

```cpp
systemctl enable docker
systemctl start docker
```

## 换源

```cpp
mkdir /etc/docker
```

然后docker文件夹中创建一个文件`daemon.json`，写入以下内容。推荐用vim操作，nano也行，不过无论用什么只要写入成功就好了。

```json
{
    "registry-mirrors": [
    	"https://docker.m.daocloud.io",
    	"https://docker.imgdb.de",
    	"https://docker-0.unsee.tech",
    	"https://docker.hlmirror.com",
    	"https://docker.1ms.run",
    	"https://func.ink",
    	"https://lispy.org",
    	"https://docker.xiaogenban1993.com"
    ]
}
```


## 测试是否安装成功和换源成功

```cpp
docker run hello-world
```

如果输出正常，没有报错，说明你安装成功了！

恭喜你，使用了人生的第一个容器技术工具！