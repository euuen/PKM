# Arduino通过按钮控制LED

（今天有急事，没空解释了，以后在加上去把）

## 代码

```cpp
void setup(){
	pinMode(2, INPUT_PULLUP);
	pinMode(4, OUTPUT);
}

void loop(){
	// 按钮被按下了
	if (digitalRead(2) == LOW){
		digitalWrite(4, HIGH);
	}else {
		digitalWrite(4, LOW);
	}
}
```