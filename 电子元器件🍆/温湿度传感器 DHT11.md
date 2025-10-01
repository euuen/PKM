# 温湿度传感器 DHT11

## 接线

```cpp
DHT11 |  MCU
DATA     2
VCC      3.3v（看情况用5v，不过不要轻易换成5v）
GND      GND
```

## 代码

### Arduino

依赖库： **DHT sensor library**

```cpp
#include <DHT.h>

#define DHTPIN 2      // DHT11 数据引脚连接的数字引脚（例如 D2）
#define DHTTYPE DHT11 // 指定传感器类型

DHT dht(DHTPIN, DHTTYPE); // 初始化 DHT 对象

void setup() {
  Serial.begin(9600); // 启动串口通信
  dht.begin();        // 启动传感器
}

void loop() {
  delay(2000); // 等待 2 秒（DHT11 采样间隔需 ≥1 秒）

  // 读取湿度（单位：%）
  float humidity = dht.readHumidity();
  // 读取温度（单位：摄氏度）
  float temperature = dht.readTemperature();

  // 检查读取是否失败
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("读取失败，请检查传感器连接！");
    return;
  }

  // 打印结果
  Serial.print("湿度: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.println("°C");
}
```