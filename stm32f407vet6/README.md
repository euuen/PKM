由于我买的是一个杂牌作的stm32f，所以说呢。。。支持不是很好，光是烧录都要我命了。。。


# 烧录接线

![[481bc3149e508c4989199cbe0c6ac8d0.png]]


# 烧录命令

```sh
#!/usr/bin/bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program firmware.elf verify reset exit"
```