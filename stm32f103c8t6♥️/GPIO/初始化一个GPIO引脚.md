# 初始化一个GPIO引脚

## HAL版本

模板：
```c
// 使能GPIOA的时钟，一定要加上这句！！！否则初始化无效，其他组的引脚就确定一下是A还是B，然后相应的改一下就好了
_HAL_RCC_GPIOA_CLK_ENABLE();

GPIO_InitTypeDef GPIO_InitStruct = {0};

// 给引脚一个初始值
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
GPIO_InitStruct.Pin = GPIO_PIN_2;
// 推挽输出模式
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

// 初始化
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
```