# 烧录程序到stm32中

我一开始想用cubeide省事情，结果一直提示说要更新固件，我一开始以为我自己的stm是不是是垃圾芯片，无法更新，于是特意买了个进口的。结果后面货来了，插上去，也提示无法更新固件。于是到这，我就开始怀疑是不是cubeide的问题了。我开始尝试用其他的软件烧录程序。

我看到了openocd。

DeepSeek告诉我如何使用openocd把编译好的elf文件烧录进stm32中。假设你用的调试器是stlink-v2，用的芯片四stm32f1系列的，那么命令是这样的：
```sh
openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program firmware.elf verify reset exit"
```

这里面的firmware.elf就是你编译出来的elf文件，文件名字要根据实际情况更改。

然后真的成功了，程序被成功烧录进去了。

破cubeide，我还以为我出<span style="color: red;">问题</span>了。我后面测试了一下，我原来那个芯片是可以的。服了，破cubeide。