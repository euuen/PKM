# cubemx真实太雕了

cubemx是用来生成stm32项目的，我感觉cubemx比那个cubeide内嵌的cubemx更加强大，他居然可以直接生成cmakelists，不过不知道为什么，就是需要自己在修改一下cmakelsit，以达到目的。

其实最主要方便的一点就是他，可以直接帮我生成好带有freertos的stm32项目，什么外设都不需要我自己管理，cubemx会自动添加，这点还是比较爽的。

主要是cubemx对ubuntu也有支持好吧，这一点更爽了。

cubemx有哪些亮点让我非常喜欢呢？下面我一个一个介绍

## 为每一个外设生成单独的.c/.h文件

这个真的太方便了，怎么设置呢？

点击project manager，然后点击Code Generator，点击Generate peripheral initialization as a paif of '.c/.h' files per peripheral（为每一个外设生成单独的.c/.h）文件。

![[Pasted image 20251105174419.png]]


## 生成CMakelists项目

点击project Manager然后，选择Toolchain/IDE 为CMake就好了，真的很爽的。

![[Pasted image 20251105175005.png]]

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

## 快速设置PWM



