# 关键HAL库使用ADC

## 同步读取ADC的值

```cpp
HAL_ADCEx_Calibration_Start(&hadc1); // 校准ADC
HAL_ADC_Start(&hadc1); // 开始读取ADC
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // 等待ADC读取完毕
int value = HAL_ADC_GetValue(&hadc1); // 获取ADC值
float voltage = (value / 4095.0f) * 3.3f; // 转换为实际电压
```

## 异步读取ADC的值

在cubemx中设置持续转换

![[Pasted image 20251206182933.png]]

```cpp
HAL_ADCEx_Calibration_Start(&hadc1); // 校准ADC
HAL_ADC_Start(&hadc1); // 开始读取ADC
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // 避免读取默认值

for (;;){
	int value = HAL_ADC_GetValue(&hadc1); // 获取ADC值
	float voltage = (value / 4095.0f) * 3.3f; // 转换为实际电压
}
```


