# HAL_TIM_Base_MspInit

TIM外设的​**​基础硬件使能​**​（与模式无关）。此函数是Callback函数，需要时需要自己手动定义。在调用 `HAL_TIM_Base_Init()`时自动触发。

## 例子

```c
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}
```