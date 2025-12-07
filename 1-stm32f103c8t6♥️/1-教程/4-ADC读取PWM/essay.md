# 如何用ADC读取PWM

## PWM的参数是什么意思

PWM接的是APB2上的时钟线，一般STM32设置的都是72Mhz的，APB2也一般是72MHz

预分频器一般设置为72-1（为什么减1？因为是stm32是从0开始计数的）

如果自动重装载器设置为100-1（为什么减1？因为是stm32是从0开始计数的）,那么pwm输出的频率是10KHz。

## CubeMX配置ADC和PWM以及USART（调试通信）

下面是在cubemx中相关的配置

### 起手式

![[Pasted image 20251106091915.png]]


![[Pasted image 20251106091937.png]]

把主频设置为72Mhz，ADC 预分频器设置/6

![[Pasted image 20251106092000.png]]


设置项目为CMake项目

![[Pasted image 20251106092428.png]]

为每一个外设生成单独的文件
![[Pasted image 20251106092515.png]]


### ADC

![[Pasted image 20251105234514.png]]


### PWM

![[Pasted image 20251105234459.png]]

### USART

![[Pasted image 20251105234542.png]]

做完之后，点击生成代码（generate code）就好了

![[Pasted image 20251106092130.png]]


## 代码部分

### 配置cmakelists

在cmakelists.txt中添加这些代码

```cmake
# 设置编译器
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)  # 避免编译器检查

# 处理器架构设置
set(LINKER_SCRIPT ../STM32F103XX_FLASH.ld) # 根据实际路径尝试要用.ld文件
add_definitions(-DSTM32F103xB)
add_compile_options(-mcpu=cortex-m3 -mthumb -fdata-sections -ffunction-sections)
add_link_options(-mcpu=cortex-m3 -mthumb -specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT} -Wl,--gc-sections)

# 添加浮点输出
add_link_options(-u _printf_float)
```

### 重定向printf

在usart.c文件中添加

```cpp
#include <unistd.h> // 注意头文件要放在前面

int _write(int file, char *ch, int len) {
  HAL_UART_Transmit(&huart1, (uint8_t *)ch, len, HAL_MAX_DELAY);
  return len;
}
```

### 核心代码部分

讲了这么久，终于到核心部分了是把，其实前面主要是为了告诉你cubemx的用法，因为，我发现还是有很多人不会用cubemx的，所以这次讲得比较详细。

那么讲了这么久，怎么进行ADC采样呢？

你需要下面的代码，进行校准，ADC采样校准之后更准确

```cpp
HAL_ADCEx_Calibration_Start(&hadc1);
```

然后开始采样

```cpp
HAL_ADC_Start(&hadc1); // 开始读取ADC
```

等待采样完成

```cpp
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // 等待ADC读取完毕
```

读取采样值

```cpp
int value = HAL_ADC_GetValue(&hadc1); // 获取ADC值
```

转化为实际电压值

```cpp
float voltage = (value / 4095.0f) * 3.3f; // 转换为实际电压
```

上面就是一些关于adc的配置，下面讲一下pwm的

```cpp
HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // 启用PWM输出
```

设置占空比

```cpp
__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 20);
```

然后，我们知道，PWM输出的只是方波，不是平滑的波，所以说，用ADC采样的时候，我们大概率只能采集到两个值，要么是3.3v 要么是0.1v

怎么办呢？我想到的方法是采样，请看下面的关键代码

```cpp
/* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 20);

HAL_ADCEx_Calibration_Start(&hadc1);
HAL_ADC_Start(&hadc1); // 开始读取ADC
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // 等待ADC读取完毕
/* USER CODE END 2 */

/* Infinite loop */
/* USER CODE BEGIN WHILE */
while (1){
	int amout = 0;
	for (int i = 0;i < 1000;i++){
		amout += HAL_ADC_GetValue(&hadc1); // 获取ADC值
	}
	int value = amout / 1000;
	float voltage = (value / 4095.0f) * 3.3f; // 转换为实际电压
	printf("%d : %.2fv\n", value, voltage);
	HAL_Delay(1000);
	/* USER CODE END WHILE */
	
	/* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
```

这里，我采样了1000次，然后最后也是发现读取到的值也是正常的了。台爽了，一下子弄明白ADC和PWM。

## 参考资料

1. [[1-stm32f103c8t6♥️/9-通信/USART通信/重定向printf]]
2. [[输出浮点数]]
3. [[1-stm32f103c8t6♥️/2-不错的文章/cubemx太雕了/main]]
