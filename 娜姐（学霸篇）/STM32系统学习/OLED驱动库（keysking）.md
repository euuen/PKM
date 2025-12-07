猜猜我是谁。嬉戏。
偷偷在这里拉屎

### 初始化与控制函数
- `OLED_Init()`- 初始化OLED屏幕
- `OLED_DisPlay_On()`- 开启显示
- `OLED_DisPlay_Off()`- 关闭显示
- `OLED_SetColorMode()`- 设置颜色模式（正常/反色）
### 帧缓冲区管理
- `OLED_NewFrame()`- 开始新的一帧，清空显存
- `OLED_ShowFrame()`- 将显存内容显示到屏幕
### 基本绘图函数
- `OLED_SetPixel()`- 设置单个像素点
- `OLED_DrawLine()`- 绘制直线
- `OLED_DrawRectangle()`- 绘制矩形边框
- `OLED_DrawFilledRectangle()`- 绘制填充矩形
- `OLED_DrawTriangle()`- 绘制三角形边框
- `OLED_DrawFilledTriangle()`- 绘制填充三角形
- `OLED_DrawCircle()`- 绘制圆形边框
- `OLED_DrawFilledCircle()`- 绘制填充圆形
- `OLED_DrawEllipse()`- 绘制椭圆
### 文本显示函数
- `OLED_PrintASCIIChar()`- 显示单个ASCII字符
- `OLED_PrintASCIIString()`- 显示ASCII字符串
- `OLED_PrintString()`- 显示字符串（支持中文）
### 5. 图像显示
- `OLED_DrawImage()`- 显示位图图像

```c
// 1. 初始化I2C后等待20ms
HAL_Delay(20);

// 2. 初始化OLED
OLED_Init();

// 3. 开始绘制新帧
OLED_NewFrame();

// 4. 绘制内容
OLED_DrawRectangle(0, 0, 128, 64, OLED_COLOR_NORMAL);
OLED_PrintString(10, 10, "Hello World", &font16x16, OLED_COLOR_NORMAL);

// 5. 显示到屏幕
OLED_ShowFrame();
```

```c
// 显示ASCII文本（使用16x8字体）
OLED_PrintASCIIString(0, 0, "ASCII Text", &afont16x8, OLED_COLOR_NORMAL);

// 显示中英文混合文本
OLED_PrintString(0, 20, "中文English混合", &font16x16, OLED_COLOR_NORMAL);
```

```c
// 绘制图形
OLED_DrawLine(0, 0, 127, 63, OLED_COLOR_NORMAL);
OLED_DrawFilledCircle(64, 32, 20, OLED_COLOR_NORMAL);
OLED_DrawImage(0, 0, &bilibiliImg, OLED_COLOR_NORMAL);
```