# 生成FreeRTOS项目+vscode

下载一个cubemx（用于生成stm32f103c8t6项目的工具，如果你没有也没有关系，我可以给你debs包，windows的没有下载，因此支持的是ubuntu）

## 设置Serial Debug

打开SYS选项

![[Pasted image 20251104150336.png]]

设置Debug选项为Serial Wire，不设置这个就上传代码，stm32就变成废铁了。（当然也没那么严重，还是有机会挽救的，只是比较麻烦）

## 设置STM32时钟为72MHz

打开`RCC`，设置`HSE`（告诉时钟）外部晶振（一般的stm32开发版上面有一个晶振，在芯片旁边，不需要你自己弄一个的）

![[Pasted image 20251104150602.png]]

然后点击`Clock Configuration`

![[Pasted image 20251104151100.png]]

电机HCLK（MHz）下面的框，修改为72，神奇的cubemx会自己修改其他地方配置以达到HCLK为72MHz的目的。

## 设置FreeRTOS接口

首先点击 Middleware开头的那个选项，然后 点击FreeRTOS，选择CMSIS_V2的接口就好了。

![[Pasted image 20251104152328.png]]

## 设置项目为CMake项目

点击Project Manager，选择Toolchain/IDE 为 CMake

![[Pasted image 20251104152511.png]]


## 修改CMakeLists

在上述工作完成后，保存并生成代码，其中会弹出一个警告，说FreeRTOS和HAL用的时钟SysTick冲突了，让HAL库不要占用SysTick中断。你点确定就好了。

但是，我真的服了，这个破cubemx，生成的cmakelists居然是有问题的。我在我的ubuntu系统上make居然失败了，逆天，不过还好这个问题比较容易解决。

只需要在cmakelists添加下面的代码就好了

```cmake
# 设置编译器
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)  # 避免编译器检查

# 处理器架构设置
set(LINKER_SCRIPT ../STM32F103XX_FLASH.ld) # 根据实际路径尝试要用.ld文件
add_definitions(-DSTM32F103xB)
add_compile_options(-mcpu=cortex-m3 -mthumb -fdata-sections -ffunction-sections)
add_link_options(-mcpu=cortex-m3 -mthumb -specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT} -Wl,--gc-sections)
```

this be like

![[Pasted image 20251104154514.png]]

## 编译项目

创建一个build文件夹，然后在build文件夹里面执行下面的命令，初始化cmake项目。

```sh
cmake ..
```

然后编译

```sh
make
```

