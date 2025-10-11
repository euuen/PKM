# 没必要记住每一行代码

搞stm32的，最难的部分其实在于通信吧，我觉得应该是的。其实芯片本身没什么好学的，就中断模式和GPIO的八大模式。所以，善用好烂笔头可以极大的提高你的开发速度。

还有一个就是，本项目如果不出意外的话，应该会大量使用HAL库（用标准库太头疼了。。。哎～～，我脑子比较笨）

与外设通信不是最难的，最难的是实现项目的核心算法。。。如何又快有准？这是开发者最核心的问题。

## 省流STM32有哪些片上外设

1. 串口通信，5个，其中（3个个USART，2个UART）
2. I2C，2个
3. SPI
4. CAN
5. USB
6. TIM

## 参考资料
1. 【【STM32入门教程】应该是全B站最好的STM32教程了！！】 https://www.bilibili.com/video/BV12v4y1y7uV/?share_source=copy_web&vd_source=d8165ccc8db4f797937e2198122cfca4
2. https://docs.keysking.com/docs/stm32/intro