# USART通信

#STM32-HAL开发

## 基本介绍

这个通信方式我又叫他TTL通信，就是说，让低电平代表0，高电平代表1。一次发送10bit的数据，起始位用1表示数据开始，结束位用0表示数据结束（一般的配置就是这样，当然你也可以改，不过改了也没什么意义，也提升不了通信效率）。两端约定好波特率才可以通信。基本的原理就是这么个原理，挺简单的，关键的难点在于stm32代码的编写。物理引脚的连接也很简单，就是RX连TX，TX连RX就好了，然后GND连GND以公地。

stm32要用USART通信，只有固定的引脚才可以配置。下图即为对应引脚的相关配置。

![[Pasted image 20250813111256.png]]

这里省流解释一下USART和UART，你只需要知道USART比UART高级就行了，USART支持异步和同步收发信息，UART支持异步的。

## 代码实现

我这里选择的是USART2（及PA3和PA2），因为我这样拉线比较方便。

我们首先需要先初始化GPIO的引脚。当然初始化GPIOA的时候不要忘记使能GPIOA的时钟了哦！！要不然配置无效。我们同时也要使能USART2的时钟，这样配置才有效。

```c
// 使能GPIOA时钟
__HAL_RCC_GPIOA_CLK_ENABLE();
// 使能USART2时钟
__HAL_RCC_USART2_CLK_ENABLE();

GPIO_InitTypeDef GPIO_InitStruct = {0};

// 2. 配置PA2(TX）
GPIO_InitStruct.Pin = GPIO_PIN_2;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // 复用推挽输出
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速模式
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// 配置PA3(RX)
GPIO_InitStruct.Pin = GPIO_PIN_3;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // 浮空输入模式
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
```

初始完GPIO后，我们就要初始化USART2了。你按照这个配置来就好了，不需要改什么。

```c
UART_HandleTypeDef huart2; // 这是一个全局变量，需要自己声明

huart2.Instance = USART2; // 选择USART2
huart2.Init.BaudRate = 115200; // 波特率
huart2.Init.WordLength = UART_WORDLENGTH_8B; // 8位数据
huart2.Init.StopBits = UART_STOPBITS_1; // 1位停止位
huart2.Init.Parity = UART_PARITY_NONE; // 无校验位
huart2.Init.Mode = UART_MODE_TX_RX; // 收发模式
huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; // 无硬件流控
huart2.Init.OverSampling = UART_OVERSAMPLING_16; // 16倍过采样

HAL_UART_Init(&huart2); // 应用配置
```

那么在初始完这两个外设之后，我们就可以发送消息了。（接受信息还需要设置中断）

```c
char data[] = "我好想你，在每个夜里；猜不透你，褪色的熟悉。\n";
while(1){
	// 200为发送最大等待时间
	HAL_UART_Transmit(&huart2, (uint8_t*) data, strlen(data), 200);
	// 每隔一秒发送一次消息
	HAL_Delay(1000);
}
```

最后编译的时候，要注意启用USART外设，这个最好在cmake中配置：

```c
# 启用UART模块
add_definitions(-DHAL_UART_MODULE_ENABLED)
```

编译，烧录，一气呵成！那么现在问题来了，怎么查看这个串口发送的信息呢？

## 串口调试工具

因为我是Arch Linux用户，而众所周知，Linux非常安全，这个串口的读写权限一般是只有root用户才有的。插上usb-ttl设备，应该电脑上有这个串口`/dev/ttyUSB0`，我们查看一下这个串口文件的权限。

```sh
euuen@archlinux ~> ls -l /dev/ttyUSB0                             

crw------- 1 root uucp 188, 0  8月13日 21:19 /dev/ttyUSB0
```

可以看到，只有root用户才可以读写这个串口。

有两个办法解决权限问题。

1. （推荐）把自己添加到uucp用户组（我是Linux，所以是uucp，ubuntu好像是另一个，我不记得了），然后重启电脑
```sh
sudo usermod -aG uucp $USER
```

2. （最快）直接修改串口权限为666（意思是全用户可以读写），这有个缺点就是，拔下来后重新插上去要在执行一遍这个代码。
```sh
sudo chmod 666 /dev/ttyUSB0
```

解决完权限问题后打开【在线串口调试工具】 https://serial.baud-dance.com/ ，选择设备，确定波特率和stm32上设置的一致，然后你就可以看到stm32每隔一秒发送过来的消息了！！！

## 处理不定长数据

对于不定长数据，通常使用空闲中断（IDLE）检测帧结束：

## 关于可移植代码

这个代码是建立在HAL库之上的，你需要自己根据你自己项目的需要移植代码。风格是尽量偏Arduino的。

注意，可能需要你自己include头文件。。。就是`#include "stm32f1xx_hal.h"`。

## 参考资料
1. 【【keysking的STM32教程】 第8集 STM32的串口通信】 https://www.bilibili.com/video/BV1Na4y1T7VQ/?share_source=copy_web&vd_source=d8165ccc8db4f797937e2198122cfca4
2. 【 STM32之USART-串口通信（含串口实验详细解析）】 https://blog.csdn.net/AriesPIG/article/details/119840979?fromshare=blogdetail&sharetype=blogdetail&sharerId=119840979&sharerefer=PC&sharesource=qq_72984050&sharefrom=from_link
## 实验工具
1. 【在线串口调试工具】 https://serial.baud-dance.com/