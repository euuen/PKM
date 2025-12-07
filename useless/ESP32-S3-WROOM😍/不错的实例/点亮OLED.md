# 点亮OLED

#ArduinoIDE开发

我不知道为什么我用标准库就会有问题，就是会花屏。但是我用stm32，自己手动搓驱动就没问题。所以，我就打算自己搓一个标准库了。

这个实例也就相当于是I2C教程了，哈哈哈。

要进行I2C通信，我们要引入Wire库。

> 这里面有一个坑就是，虽然ESP32说，任意两个引脚都是支持I2C，但是我无论用其他的什么引脚都会报错。只能用8、9引脚分别作为SDA、SCL才行。挺奇怪的。

## 使用I2C进行通信

首先把引脚连接好

```cpp
OLED | ESP32
VCC -> 5v
SCL -> 8
SDA -> 9
GND -> GND
```

我们要用Wire库来发送数据。一个示例如下：

```cpp
Wire.beginTransmission(ADDRESS);
Wire.write(data, length);
Wire.endTransmission();
```

其中的ADDRESS是一个`uint8_t`类型，data一个`const uint8_t*`类型，length是`size_t`类型。

## 参考资料

1. [[驱动库底层原理]]
2. https://blog.csdn.net/xq151750111/article/details/115142727