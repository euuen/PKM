# 改变GPIO的state

## 设置引脚状态
```c
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
```

## 反转引脚状态
```c
HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
```

# 读取GPIO的状态

```c
PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
```

