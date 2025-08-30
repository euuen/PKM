# PWM模式

## 初始化PWM Channel

```c
TIM_HandleTypeDef htim3;
TIM_ClockConfigTypeDef sClockSourceConfig = {0};
TIM_MasterConfigTypeDef sMasterConfig = {0};
TIM_OC_InitTypeDef sConfigOC = {0};

// 使能TIM3
__HAL_RCC_TIM3_CLK_ENABLE();

// 初始化TIM计数器
htim3.Instance = TIM3;
htim3.Init.Prescaler = 72-1; // 设置预分频器
htim3.Init.CounterMode = TIM_COUNTERMODE_UP; // 上升计数
htim3.Init.Period = 100-1; // 设置自动重装载指
htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
if (HAL_TIM_Base_Init(&htim3) != HAL_OK){
	Error_Handler();
}

// 配置时钟源
sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL; // 就是内部时钟源APB1
if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK){
	Error_Handler();
}

// 配置PWM Channel
if (HAL_TIM_PWM_Init(&htim3) != HAL_OK){
	Error_Handler();
}
sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE; // TIM3独立工作
if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK){
	Error_Handler();
}
sConfigOC.OCMode = TIM_OCMODE_PWM1; // 设置为PWM模式1，前半段有效后半段无效电平
sConfigOC.Pulse = 0; // 设置输出比较寄存器的值
sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH; // 设置有效电平为高电平
sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK){
	Error_Handler();
}

// 配置PWM的引脚
GPIO_InitTypeDef GPIO_InitStruct = {0};

// 使能GPIOA
__HAL_RCC_GPIOA_CLK_ENABLE();

// PA6     ------> TIM3_CH1
GPIO_InitStruct.Pin = GPIO_PIN_6;
GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
```

## 启用PWM输出

```c
//启动PWM输出
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
```

## 设置比较寄存器

```c
__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, period);
```

## PWM频率计算

PWM频率 = TIM频率 / （预分频器的值+1）/（自动重装载器的值+1）

如配置如下：
```c
htim3.Init.Prescaler = 72-1; // 设置预分频器
htim3.Init.Period = 100-1; // 设置自动重装载指
```

那么PWM的频率就是72 Mhz/ 72/ 100 = 10 kHz

## 参考资料

1. <iframe src="https://player.bilibili.com/player.html?isOutside=true&aid=1006153465&bvid=BV1Yx4y1x7xY&cid=1606468239&p=1&autoplay=0" scrolling="no" border="0" frameborder="no" framespacing="0" allowfullscreen="true" width="600" height="400"></iframe>