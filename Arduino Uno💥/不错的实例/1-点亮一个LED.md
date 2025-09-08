# 1-点亮一个LED

LED有正负两级，推荐正极连接在Uno的一个GPIO口上，负极连在Uno的GND上。

这里假设你用的是GPIO 2。

那么在Arduino中，你应该先初始化这个引脚然后才可以使用这个引脚输出高低电平。

那么点亮LED的代码如下：

```cpp
void setup(){
	// 初始化GPIO 2为推挽输出
	pinMode(2, OUTPUT);
	// 设置GPIO 2的输出为高电平
	digitalWrite(2, HIGH;
}

void loop(){

}
```

注意LED的正负极不要搞反了。正极连接GPIO 2，负极连接GND。

编译上传代码，启动～。这样你应该就可以看到你的LED亮起来了。