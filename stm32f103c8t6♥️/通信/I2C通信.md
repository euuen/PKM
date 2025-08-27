# I2C通信

```c
# 记得启用I2C模块在CMakeLists中
add_definitions(-DHAL_I2C_MODULE_ENABLED)
```

## 初始化I2C1外设代码
```c
I2C_HandleTypeDef hi2c1;

static void MX_I2C1_Init(void){
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;       // 标准模式400kHz或者100kHz
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2; // 标准模式固定使用2:1占空比
    hi2c1.Init.OwnAddress1 = 0;           // 主模式无需设置自身地址
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler(); // 初始化失败处理
    }
}
```

## 初始化I2C1引脚代码
```c
static void MX_GPIO_Init(void){
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	
	// 配置PB6(SCL)和PB7(SDA)
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;       // 复用开漏输出
    GPIO_InitStruct.Pull = GPIO_PULLUP;            // 内部上拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速模式
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
```

## 判断I2C设备是否准备好了

```c
#define I2C_ADDRESS 0x78（OLED的I2C地址）

if (HAL_I2C_IsDeviceReady(&hi2c1, I2C_ADDRESS, 3, 100) == HAL_OK) {
	// 设备就绪
} else {
	// 设备未找到
}
```

## 主机发送信息

```c
HAL_I2C_Master_Transmit(&hi2c1, ADDRESS, data, size, HAL_MAX_DELAY);
```