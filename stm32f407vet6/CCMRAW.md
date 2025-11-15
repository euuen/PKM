# 什么是CCMRAW

你就简单的把他当成一个高速缓存就好了。

怎么把变量或者函数缓存在这上面呢？

最好定义一个宏

```cpp
#define CCMRAM __attribute__((section(".ccmram")))
```

然后在变量或者函数前面加上`CCMRAM`就好了

```cpp
CCMRAM void ISR(){

}

CCMRAM int n = 0;
```

但是，注意一下，这个CCMRAM变量在复位（如果一直有电）的时候不会重新初始化，请在初始化系统的时候自己手动初始化一下。