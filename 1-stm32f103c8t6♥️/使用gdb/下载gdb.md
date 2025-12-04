# 下载gdb

## 参考资料

1. 【Ubuntu上下载并且安装arm-none-eabi-gdb】 https://blog.csdn.net/weixin_41328027/article/details/123022209

我不知道为什么ubuntu上的gcc-arm-none-eabi包没有带有gdb，还要我自己手动安装一遍，简直无语。

首先从官网上面下载下来，然后复制到/usr/share文件夹下面创建符号连接

```sh
sudo ln -s /usr/share/gcc-arm-none-eabi-your-version/bin/arm-none-eabi-gdb /usr/bin/arm-none-eabi-gdb
```

注意，这个your-version需要替换一下

然后，还要创建一个链接，是关于gdb的依赖的

```sh

sudo apt install libncurses-dev
sudo ln -s /usr/lib/x86_64-linux-gnu/libncurses.so.6 /usr/lib/x86_64-linux-gnu/libncurses.so.5
sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6 /usr/lib/x86_64-linux-gnu/libtinfo.so.5
```

