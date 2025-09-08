# 1-点亮自带的LED

#STM32-HAL开发

这个自带的LED接在PC13引脚上面，所以我们需要使能GPIOCd时钟，然后初始化PC13引脚。

```c
GPIO_InitTypeDef GPIO_InitStruct = {0};

// 使能GPIOC时钟
__HAL_RCC_GPIOC_CLK_ENABLE();

// 初始化PC13引脚
GPIO_InitStruct.Pin = GPIO_PIN_13;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

// 给PC13一个低电平，低电平才可以点亮LED💡
HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
```

把这段代码放在while循环前面（不要放在里面），build然后烧录之后，你应该就可以看到你的stm32上的一个LED点亮了

![[1755062808339.jpg]]

我这里的就是这个绿色LED亮了。

如果你做到这一步成功了，那么恭喜你，成功迈出了嵌入式的第一步！！！

现在来升级一下，让这个LED闪烁起来。怎么实现呢？答案是利用HAL_Delay函数

```c
while(1){
	// 点亮LED
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	// 持续亮200ms
	HAL_Delay(200);
	// 熄灭LED
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	// 持续熄灭200ms
	HAL_Delay(200);
}
```

那么，效果应该是这样的。
![[video_20250813_133048.mp4]]