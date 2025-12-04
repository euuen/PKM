# 用DAC播放音乐

首先你需要获取音乐文件，这里我推荐你随便搜索一个网易云在线解析，搜索你喜欢的音乐然后下载下来。

一般这个文件是mp3，然后用ffmpeg把他转为wav文件

```sh
ffmpeg -i music.mp3 music.wav
```

然后，我们需要压缩码率，因为stm32一般放不下

```sh
ffmpeg -i aqxx.wav -ar 4000 -ac 1  -ss 00:00:00 -t 20 aqxx1.wav
```

1. -i 表示输入文件
2. -ar 4000 表示采样率为4000
3. -ac 1 表示单通道
4. -ss 起始时间
5. -t 持续时间（和-ss一般用于裁减）

然后用下面的python代码转换数据，我们需要原始的高低电平数据。

```python
import wave
import array
import os

def extract_and_convert_pcm(wav_file_path, output_c_file="dac_data.c"):
    """
    从WAV文件提取PCM数据并转换为适合DAC的格式，然后保存为C数组文件
    
    参数:
    wav_file_path: 输入的WAV文件路径
    output_c_file: 输出的C文件名
    """
    try:
        with wave.open(wav_file_path, 'rb') as wav_file:
            # 获取音频参数
            n_channels = wav_file.getnchannels()
            samp_width = wav_file.getsampwidth()  # 样本宽度（字节数）
            frame_rate = wav_file.getframerate()
            n_frames = wav_file.getnframes()
            
            print(f"音频参数: 声道数={n_channels}, 采样宽度={samp_width}字节, 采样率={frame_rate}Hz, 总帧数={n_frames}")
            
            # 读取所有帧数据
            frames = wav_file.readframes(n_frames)
            
            # 根据样本宽度将二进制数据转换为整数
            if samp_width == 2:
                # 16位有符号整数（小端序）
                samples = array.array('h', frames)  # 'h' 表示有符号短整数
            else:
                raise ValueError("仅支持16位PCM WAV文件")
        
        # 转换为DAC数据 (12位格式: 0-4095)
        dac_data = []
        for i in samples:
            # 将有符号16位(-32768到32767)转换为无符号12位(0-4095)
            # 方法: (i + 32768) >> 4
            dac_value = (i + 32768) >> 4
            # 确保值在0-4095范围内
            dac_value = max(0, min(4095, dac_value))
            dac_data.append(dac_value)
        
        # 生成C文件
        generate_c_file(dac_data, output_c_file, frame_rate, n_channels, len(dac_data))
        
        print(f"转换完成! 共处理 {len(dac_data)} 个样本")
        print(f"DAC数据范围: {min(dac_data)} 到 {max(dac_data)}")
        print(f"C文件已生成: {output_c_file}")
        
        return dac_data, frame_rate
        
    except Exception as e:
        print(f"错误: {e}")
        return None, None

def generate_c_file(dac_data, output_file, sample_rate, channels, num_samples):
    """
    生成包含DAC数据的C语言数组文件[6](@ref)
    """
    # 获取文件名（不含扩展名）用于变量命名
    base_name = os.path.splitext(os.path.basename(output_file))[0]
    # 清理变量名，只保留字母数字和下划线[3](@ref)
    var_name = ''.join(c if c.isalnum() else '_' for c in base_name)
    if var_name[0].isdigit():
        var_name = 'audio_' + var_name
    
    with open(output_file, 'w') as f:
        # 写入文件头和信息[3](@ref)
        f.write("/* DAC音频数据 - 自动生成 */\n")
        f.write("/* 来源: %s */\n" % os.path.basename(output_file.replace('.c', '.wav')))
        f.write("/* 采样率: %d Hz, 声道数: %d, 样本数: %d */\n\n" % 
                (sample_rate, channels, num_samples))
        
        f.write("#include <stdint.h>\n\n")
        
        # 定义音频参数宏[3](@ref)
        f.write("/* 音频参数 */\n")
        f.write("#define %s_SAMPLE_RATE    %d\n" % (var_name.upper(), sample_rate))
        f.write("#define %s_NUM_CHANNELS   %d\n" % (var_name.upper(), channels))
        f.write("#define %s_NUM_SAMPLES    %d\n\n" % (var_name.upper(), num_samples))
        
        # 开始数组定义[2](@ref)
        f.write("/* DAC数据数组 (12位: 0-4095) */\n")
        f.write("const uint16_t %s_data[%s_NUM_SAMPLES] = {\n" % (var_name, var_name.upper()))
        
        # 写入数据，每行10个元素[3](@ref)
        for i, value in enumerate(dac_data):
            if i % 10 == 0:
                f.write("    ")
            
            f.write("0x%03X" % value)  # 12位数据用3位十六进制表示
            
            if i < len(dac_data) - 1:
                f.write(", ")
            
            # 每10个元素换行
            if (i + 1) % 10 == 0 and i < len(dac_data) - 1:
                f.write("\n")
        
        f.write("\n};\n\n")
        

# 使用示例
if __name__ == "__main__":
    try:
        # 转换WAV文件
        # 注意修改文件名
        dac_data, sample_rate = extract_and_convert_pcm("aqxx1.wav", "dac_audio_data.c")
        
        if dac_data:
            # 显示前10个样本值作为验证
            print("\n前10个DAC数据值:")
            for i in range(min(10, len(dac_data))):
                print("样本[%d]: 原始=0x%03X, 十进制=%d" % (i, dac_data[i], dac_data[i]))
                
    except Exception as e:
        print(f"执行错误: {e}")
```

这样就会生成一个c文件，你链接到你的项目里面直接用就好了。

然后在cubemx中这么配置就好了

我这里用的是dma和tim6定时器（专门为dac设计的tim），所以，需要配置下面的内容


![[Pasted image 20251116220358.png]]

![[Pasted image 20251116220454.png]]

![[Pasted image 20251116220743.png]]

在一切都设置好了之后，就可以写代码了。

```cpp
/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  extern uint16_t dac_audio_data_data[];
  // HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_TIM_Base_Start(&htim6); // 打开TIM6
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)dac_audio_data_data, 28000, DAC_ALIGN_12B_R); // dma搬运数据
  
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}
```

但是这样的话，有一个缺点，就是只能播放很短的时间，因为stm32容量有限。