# 重定向printf

我不知道为什么，网上都是用下面这个代码的（我无语了，我发现我用下面不能解决问题）

```cpp
#include <stdio.h>

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int _io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__*/


PUTCHAR_PROTOTYPE {
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}
```

后面，我用下面的代码就好了

```cpp
#include <unistd.h>

int _write(int file, char *ch, int len)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)ch, len, HAL_MAX_DELAY);
  return len;
}
```


# 特别注意

如果没有输出的话，请注意你有没有刷新缓冲区！

**有没有\n!!!**，**一定要有\n阿！！！！**

