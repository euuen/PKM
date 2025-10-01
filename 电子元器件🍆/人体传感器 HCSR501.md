# 人体传感器 HCSR501

## 接线

```cpp
 HC-SR501       |     Arduino
 VCC                  3.3v（看情况用5v，不过不要轻易换成5v）
 GND                  GND
 OUT                  4
```

## 代码

### Arduino

```cpp
int sensorPin = 4;  // HC-SR501 的 OUT 引脚连接到的 Arduino 数字引脚
int ledPin = 13;    // LED 连接的引脚（板载LED）

void setup() {
  pinMode(sensorPin, INPUT);   // 设置传感器引脚为输入模式
  pinMode(ledPin, OUTPUT);     // 设置LED引脚为输出模式
  Serial.begin(9600);          // 初始化串口通信，便于调试观察
}

void loop() {
  int motion = digitalRead(sensorPin);  // 读取传感器引脚的状态

  if (motion == HIGH) {          // 如果检测到人体移动
    digitalWrite(ledPin, HIGH);  // 点亮LED
    Serial.println("检测到人体移动！"); // 打印信息到串口监视器
  } else {
    digitalWrite(ledPin, LOW);   // 否则关闭LED
  }
  
  delay(50);  // 短暂的延迟，有助于稳定读取信号
}
```