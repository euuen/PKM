# 重定向printf

之前一直都是用真的串口，可以ch340还是比较难安装的，总是一不小心就装错，而且还要考虑波特率之类的巴拉巴拉的东西。

我后面学到了usb，后面干脆直接用usb来调试算了，因为usb我根本用不到好吧。。。而且貌似usb的速度更快呢，而且usb和波特率无关，随便你用什么波特率反正都不会影响结果，这不是更人性化呢？

参考之前用usart做的printf[[1-stm32f103c8t6♥️/9-通信/USART通信/重定向printf]]，不能难写出用usb改造后的版本

```cpp
#include <unistd.h>
#include "usbd_cdc.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

int _write(int file, char *ch, int len)
{
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, (uint8_t*)ch, len);//把接收到的数据拷贝到发送
  USBD_CDC_TransmitPacket(&hUsbDeviceFS);//发送
  return len;
}
```