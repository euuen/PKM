# 用USB虚拟串口给电脑发送信息

## 参考资料

1. 【零基础STM32单片机编程入门(三十) USB口介绍及CDC类虚拟串口通讯详解及源码】 https://gzwelink.blog.csdn.net/article/details/141102355

参考资料把很多基本概念都讲的差不多了，我这里主要写一些我自己写代码遇到的小问题了。

## 神人STM32把usb句柄藏起来

我们要使用usb的相关函数的时候需要usb句柄，但是我发现他不再头文件中。。。无语了，依法半导体，你在搞什么。

后面全局搜索，发现这玩意儿在`usb_device.c`中睡大觉呢。后面我直接用extern修饰一下才好的。

```cpp
extern USBD_HandleTypeDef hUsbDeviceFS;
```

## 发送信息

```cpp
USBD_CDC_SetTxBuffer(&hUsbDeviceFS, (uint8_t*)"hello usb", sizeof("hello usb"));//把接收到的数据拷贝到发送
USBD_CDC_TransmitPacket(&hUsbDeviceFS);//发送
```

