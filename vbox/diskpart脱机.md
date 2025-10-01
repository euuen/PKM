# diskpart脱机

我为什么把diskpart弄到这个区域里面呢？因为vbox需要。

根据我同学的经验，不知道为什么设备管理器里面的脱机，好像是假脱机，建议用命令行来进行脱机。

打开CMD，输入`diskpart`

然后，比如我要脱机DISK2

```sh
DISKPART> list disk

  磁盘 ###  状态           大小     可用     Dyn  Gpt
  --------  -------------  -------  -------  ---  ---
  磁盘 0    联机              476 GB  1024 KB        *
  磁盘 1    联机              476 GB      0 B        *
  磁盘 2    联机              476 GB  1024 KB        *
```

我们就可以这样：

```sh
DISKPART> select disk 2

磁盘 2 现在是所选磁盘。

DISKPART> offline disk

DiskPart 成功使所选磁盘脱机。
```

聪明的读者应该一下就能看懂了把。。。