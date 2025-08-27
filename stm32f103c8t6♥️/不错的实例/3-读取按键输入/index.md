# 3-读取按键输入

## 省流：配置和使用

假设你要用的引脚是PB12，那么PB12的初始化配置如下：

```c
// 不要忘记使能GPIOB时钟！！！
__HAL_RCC_GPIOB_CLK_ENABLE();

GPIO_InitTypeDef GPIO_InitStruct = {0};

GPIO_InitStruct.Pin = GPIO_PIN_12;
// 输入模式
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
// 上拉输入
GPIO_InitStruct.Pull = GPIO_PULLUP;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
```

如何读取呢？

```c
// 代表按键已经按下
if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET){
	// 削抖代码
	HAL_Delay(10);
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET){
		// 处理代码
	}
}

// 按键已经松开
if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET){
	// 削抖代码
	HAL_Delay(10);
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET){
		// 处理代码
	}
}
```

## 1. 为什么RESET代表按下？

这需要回到stm32的引脚原理图了。

![[Pasted image 20250815100348.png]]
（这个是我从一个up视频里面裁剪的图。。。没关系，能讲个大概就可以了）

从原理图来看，当KEY没有按下的时候，右边的电路处于一个断路的状态，所以，电流只能流向左边这条电路了。

然后，你只要知道当stm32的引脚处于输入模式的时候，引脚内部相当于串联了一个非常大的电阻，所以，那个电阻$R_{11}$根本分不到电压，所以stm32读取到的就是高电平了。

但KEY按下的时候，那么电流会流向右边了，那么左边就分不到什么电压了，所以，此时stm32读取到的就是低电平。

这就是为什么当KEY按下的时候，stm32读取到的就是低电平，而松开的时候是高电平。

## 2. 为什么要上拉一个电阻？

你不上拉一个电阻，电源3.3v和GND直接连接不得烧坏完了？

## 3. 我可以下拉输入吗？

可以的。不过你不觉得这有点奇怪吗。。。因为大家一般都是一端连GPIO口另一端连GND，你这样有点奇怪。

然后第二个是稳定性的问题。低电平只要接近0v就算是低电平了，那高电平呢？其实不是很好判断。所以低电平具有天然的抗干扰性。

最后一个是习惯问题，因为行业标准就是上拉输入。
## 参考资料

1. 【【STM32入门教程-2025】第4集 按键控制小灯 GPIO输入 | keysking的stm32教程】 https://www.bilibili.com/video/BV1Z84y157dx/?share_source=copy_web&vd_source=d8165ccc8db4f797937e2198122cfca4
