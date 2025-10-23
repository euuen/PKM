# 我的妈啊，mpu6050的dmp驱动也太难移植了八

累了累了，我想休息了。

哭了😭，我的MPU6050没有支持DMP的硬件，我只能自己手动写计算代码了，😭。

# 可移植代码

```cpp
#define MPU6050_ADDR 0x68 << 1 // HAL库需要左移1位

void MPU6050_Read(uint8_t reg, uint8_t *data, uint16_t len) {
	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}

void MPU6050_Write(uint8_t reg, uint8_t data) {
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

void MPU6050_Init(void) {
    // 唤醒设备
    MPU6050_Write(0x6B, 0x00);
    HAL_Delay(100);
    
    // 设置陀螺仪量程 ±2000°/s
    MPU6050_Write(0x1B, 0x18);
    
    // 设置加速度计量程 ±2g
    MPU6050_Write(0x1C, 0x00);
    
    // 设置低通滤波器 42Hz
    MPU6050_Write(0x1A, 0x03);
    
    // 设置采样率 1kHz/(1+4) = 200Hz
    MPU6050_Write(0x19, 0x04);
}
```


## 参考资料

1. 【STM32移植MPU6050 DMP超详细教程】 https://blog.csdn.net/2301_76950640/article/details/145891577