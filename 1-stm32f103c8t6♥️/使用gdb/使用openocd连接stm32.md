# 使用openocd连接stm32

命令：

```sh
openocd -c "gdb_port 50000" -f interface/stlink-v2.cfg -f target/stm32f1x.cfg
```