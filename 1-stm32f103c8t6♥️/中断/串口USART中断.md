# 串口USART中断

这个不需要像外部中断一样设置特殊的GPIO模式

## 启用USART中断

```c
HAL_NVIC_SetPriority(USART2_IRQn, 1, 0); // 设置中断优先级
HAL_NVIC_EnableIRQ(USART2_IRQn);         // 使能USART2中断
```

## 覆写USART中断函数

```c
void USART2_IRQHandler(void){
	HAL_UART_IRQHandler(&huart2);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if (huart->Instance == USART2){
		// 使用DMA将接收到的数据发送回去
		HAL_UART_Transmit_DMA(&huart2, rx_data, Size);
		// 重新启动接收，使用Ex函数，接收不定长数据
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rx_data, sizeof(rx_data));
		// 关闭DMA传输过半中断（HAL库默认开启，但我们只需要接收完成中断）
		__HAL_DMA_DISABLE_IT(huart2.hdmarx, DMA_IT_HT);
	}
}
```
