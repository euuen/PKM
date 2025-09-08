# 2-使用OLED

## 接线

```cpp
OLED | Arduino
VCC -> 5v
SCL -> A5
SDA -> A4
GND -> GND
```

## 必要的库

```cpp
Adafruit SSD1306
Adafruit GFX Libray
```

## 示例代码

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED 配置参数
#define SCREEN_WIDTH 128 // 屏幕宽度（像素）
#define SCREEN_HEIGHT 64 // 屏幕高度（像素）
#define OLED_ADDR 0x3C   // I2C 地址（根据你的屏幕修改，常见0x3C或0x3D）

// 初始化一个 Adafruit_SSD1306 对象
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup(){
	// 初始化dispaly
	display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
	
	// 清除显示缓冲区
	display.clearDisplay();
	
	// 设置文本大小、颜色和起始坐标
	display.setTextSize(1);      // 大小 1:1
	display.setTextColor(SSD1306_WHITE); // 绘制白色文字
	display.setCursor(0, 0);     // 起始坐标 (0,0)
	display.println("initing....."); // 打印文本
	
	// 刷新OLED
	display.display();
}

void loop(){

}
```

## 绘制文字

```cpp
// 设置文本大小、颜色和起始坐标
display.setTextSize(1);      // 大小 1:1
display.setTextColor(SSD1306_WHITE); // 绘制白色文字
display.setCursor(0, 0);     // 起始坐标 (0,0)
display.println("initing....."); // 打印文本
```
