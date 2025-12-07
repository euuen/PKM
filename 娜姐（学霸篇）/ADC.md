1. 信号类型
数字信号（高低电平）
模拟信号（任意电压值）
2. 底层原理：逐次逼近法（二分比较）*了解即可*
最大值4095（3.3V）
中间值2048（1.65V）
12位ADC
3. 代码部分
HAL_ADC_Start()函数开启ADC采集
HAL_ADC_GetValue()函数获取ADC读数value
电压值voltage=(value/4095.0) * 3.3
https://blog.csdn.net/qq_37946877/article/details/120753421

https://blog.csdn.net/rannar/article/details/81154765?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-1-81154765-blog-120753421.235^v43^pc_blog_bottom_relevance_base7&spm=1001.2101.3001.4242.2&utm_relevant_index=3
# 使用STM32CubeMX创建工程
1. 创建新工程：打开STM32CubeMX，点击"Start My project from MCU"，在搜索框输入STM32F103C8T6并双击选中。
2. 配置调试接口：在左侧"Pinout & Configuration"选项卡中，找到"System Core"下的"*SYS*"选项，*将"Debug"设置为"Serial Wire"*。这一步非常重要，它使能了SWD调试接口，避免了后续无法下载程序或调试的问题。
3. 配置时钟源：找到"System Core"下的"*RCC*"选项，将"*HSE*"设置为"*Crystal/Ceramic Resonator*"，即使用外部高速晶振。
4. 配置时钟树：点击顶部的"Clock Configuration"选项卡，在"*HCLK*"输入框输入72并回车，软件将自动配置整个时钟树，将系统主频设置为*72*MHz。
5. 配置ADC引脚：假设电池电压通过分压电路后连接到STM32的PA0引脚（它对应ADC的通道0）。在芯片引脚图上的*PA0*引脚，选择"*ADC_IN0*"功能。
6. 配置ADC参数：在左侧"*Analog*"下找到"*ADC1*"选项，进行如下关键设置：
在"ADC Settings"标签下，将"*Resolution*"设置为"*12 bits*"。
将"*Scan Conversion Mode*"设置为"*Disabled*"（单通道转换可不使用扫描模式）。
将"*Continuous Conversion Mode*"设置为"*Enabled*"（使能连续转换）。
在"*Parameter Settings*"标签下，根据信号特性设置合适的"Sampling Time"（采样时间），例如"239.5 cycles"可获得较高精度。
配置DMA（可选但推荐）：对于需要连续高速采样或减少CPU占用的应用，可以配置DMA。在"*DMA Settings*"标签页点击"*Add*"，选择"*ADC1*"，将模式设置为"*Circular*"（循环模式）。这样ADC转换的数据会自动通过DMA传输到内存，无需CPU介入。
生成工程代码：
点击"Project Manager"选项卡，设置"*Project Name*"（工程名称）和"*Project Location*"（工程路径），确保路径中不包含中文或特殊字符
。
在"Toolchain / IDE"中选择"*Cmake*"
。
点击"Code Generator"选项卡，勾选"*Generate peripheral initialization as a pair of '.c/.h' files per peripheral*"，这会使代码结构更清晰
。
最后点击"*GENERATE CODE*"生成工程。
# 在VSCode中编写和修改代码
1. 打开工程：用VSCode打开STM32CubeMX生成的工程文件夹。
2. 配置VSCode的C/C++插件：为了让VSCode的代码提示和跳转功能正常工作，需要配置头文件路径。在工程根目录下创建或修改.vscode/c_cpp_properties.json文件，包含ADC相关的头文件路径。
3. 编写ADC采样代码：在VSCode中打开Src/main.c文件。STM32CubeMX生成的代码包含了主循环while (1)，我们需要在其中添加ADC采样和电压计算的逻辑。务必在/* USER CODE BEGIN ... */和/* USER CODE END ... */注释对之间添加你的代码，这样当你在CubeMX中修改配置并重新生成代码时，你添加的代码不会被覆盖
```c
/* 在main函数开始后，找到主循环while(1) */
/* USER CODE BEGIN WHILE */
while (1)
{
    /* 启动ADC转换 */
    HAL_ADC_Start(&hadc1); // 假设你的ADC实例名为hadc1
    
    /* 等待转换完成 */
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
    {
        /* 读取转换结果 */
        uint32_t adcValue = HAL_ADC_GetValue(&hadc1);
        
        /* 将ADC值转换为电压值（假设VDDA=3.3V，12位分辨率） */
        float adcVoltage = (float)adcValue * 3.3f / 4095.0f;
        
        /* 根据分压电阻比例计算实际电池电压（例如分压比为4:1，即R1=30k, R2=10k） */
        float batteryVoltage = adcVoltage * 4.0f; // 电压 = ADC电压 * ( (R1 + R2) / R2 )
        
        /* 你可以在此处添加代码，通过串口打印电池电压，或者根据电压值进行其他逻辑判断 */
    }
    
    HAL_Delay(1000); // 每秒采样一次
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
}
/* USER CODE END 3 */
```