# 外部中断EXTI

## 设置GPIO下降沿触发中断

```c
// 1. 开启时钟 (AFIO时钟非常关键！)
__HAL_RCC_GPIOA_CLK_ENABLE();
// 如果你是从cubemx生成的项目来的话，这个已经在stm32f1xx_hal_msp.c被启用过了，也就是HAL_Init()函数中以及调用了。也就是说，你可以不必写这个。当然如果你加上其实也没有关系的，重复执行这个代码是没有问题的。
__HAL_RCC_AFIO_CLK_ENABLE();

// 2. 配置GPIO结构体并初始化
GPIO_InitTypeDef GPIO_InitStruct = {0};
GPIO_InitStruct.Pin = GPIO_PIN_5;
GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;  // 设置为下降沿触发中断
GPIO_InitStruct.Pull = GPIO_PULLUP;           // 根据你的电路选择上拉或下拉
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// 3. 配置并启用NVIC中断
// EXTI5~EXTI9的中断通道是 EXTI9_5_IRQn
HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0); // 设置优先级，数字越小优先级越高
HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);         // 使能中断通道
```

这里设置为1比较保险，因为HAL_Delay底层是依靠中断实现的，他的中断优先级是0，也就是说是最高的。设置为1就不会引起冲突，防止程序跑飞。当然如果你的中断不用HAL_Delay，那当我没说。

## 覆写中断处理函数

这两个函数都必须要覆写才行！

```c
// 外部中断[15:10]的处理函数，HAL_GPIO_EXTI_Callback从此处被调用。
void EXTI15_10_IRQHandler(void){
	// 消位中断标记，调用Callback
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
}

// 外部中断Callback，由HAL_GPIO_EXTI_IRQHandler触发
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// 再次确认是否按下KEY1
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0){
		// 绿灯翻转
		HAL_GPIO_TogglePin(GREEN_GPIO_Port, GREEN_Pin);
		// 等待按键释放
		while(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0);
	}
}
```

> 另外说一嘴`EXTI15_10_IRQHandler`的weak声明在`startup_stm32f103c8tx.s`中，`HAL_GPIO_EXTI_Callback`的weak声明在`stm32f1xx_hal_gpio.c`中。

## CubeMX项目

Cubemx中，IRQHandler相关的函数一般放在`stm32f1xx_it.c`文件中。
