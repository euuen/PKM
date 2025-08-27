# 文件目录解析

![[Pasted image 20250812172755.png]]

1. **Core**，即用户代码存放的地方。
2. **Drivers/CMSIS**，stm32的标准库
3. **Drivers/STM32F1xx_HAL_Driver**，stm32的HAL库（不能单独只用HAL库，因为HAL库依赖标准库）