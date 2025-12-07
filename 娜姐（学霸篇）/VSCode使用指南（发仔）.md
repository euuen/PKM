# 在根目录下面创建文件

![[根目录下创建文件.mp4]]

# Linux命令行

`chmod`是 Linux 和类 Unix 操作系统中用于修改文件或目录访问权限的命令，它决定了谁可以读取、写入或执行这个文件或目录

chmod +x run的意思就是改变run文件为可执行文件。

# Cmake

CMake是一个开源的、跨平台的自动化构建系统，它不直接编译代码，而是通过一个名为 `CMakeLists.txt`的配置文件，生成标准的、适用于不同操作系统和编译器的本地构建文件（例如 Unix 系统下的 Makefile 或 Windows 系统下的 Visual Studio 项目文件），然后再由相应的本地构建工具完成编译和链接工作。

|核心优势|解决了什么问题|带来的直接好处|
|---|---|---|
|**🔄 统一的跨平台构建**​|不同平台（Windows/Linux/macOS）使用不同的构建工具（如 Visual Studio, Makefile, Xcode），手动为每个平台维护构建脚本极其繁琐且容易出错。|**一份配置，多处构建**。只需编写一次 `CMakeLists.txt`，CMake 就能为不同平台生成所需的原生构建文件（如 Makefile 或 .sln 文件），极大提升了开发效率和应用的可移植性。|
|**🏗️ 强大的项目与依赖管理**​|当项目规模增长，有成百上千个文件且依赖多个内部模块和第三方库（如 OpenCV、Boost）时，手动管理编译顺序、依赖关系和链接会变得异常复杂。|**声明式项目管理**。你可以清晰地定义目标（可执行文件、库）以及它们之间的依赖关系。CMake 会自动处理复杂的构建顺序，并通过 `find_package`等命令简化外部库的查找和链接。|
|**🔧 高效的构建流程与生态集成**​|传统的构建方法缺乏标准化，且与高级功能（如自动化测试、打包分发）的集成较弱。|**功能丰富的工具链**。CMake 与 CTest（测试）、CPack（打包）紧密集成，支持依赖分析和增量编译（只重新编译改动部分），并能与 Ninja 这类高效构建工具配合，形成构建、测试、打包的一体化流水线。|
# VSCode是干吗的

我们只是把vscode作为一个代码编辑器，没错就只是一个编辑器，真正的编译工作我们是交给make的。

根据cmakelist，cmake会自己生成makefile，然后让make根据makefile来编译。
![[根目录下创建文件.mp4]]
# 什么是makefile

很早很早的时候，我们要编译c语言要自己用gcc一行一行的编译，然后自己链接，这样非常麻烦。

人们为了方便，就创建了make，用makefile规定怎么编译c项目。然后让make自己去编译，链接，这样非常好。

但是，makefile还是太难写了，要写很多废话代码。于是，人们又发明了cmake，cmake写起来非常简单，跨平台也非常简单。




用CubeMX配置好了之后，生成代码，关掉文件，在VSCode打开并*Release*，在VSCode最大的文件夹里*创建run文件*，在终端中输入*cmake --build*等，在build/Release文件夹中*查找.elf文件，复制路径*，在？？？文件中输入#!/usr/bin/bash
openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program *firmware.elf* verify reset exit"将绿色的代换成复制的路径（bulid路径前面的删去），将*compile_commands.json移动到build中*，然后VSCode终端输入*chmod +x ./run*,然后就可以在Code的Src和Inc的main.h和main.c中写代码了

文件包含​ (Includes)
*用于添加项目所需的自定义头文件*
宏定义​ (PD)
*用于定义常量、条件编译等宏*
类型定义​ (PTD)
*用于定义结构体、枚举、联合体等自定义类型*
变量定义​ (PV)
*用于定义全局变量、静态变量等*
函数声明​ (PFP)
*用于声明自定义函数的原型*
主函数内的代码段​
*用于在main函数的特定阶段（如初始化前、外设初始化后、主循环内）插入您的应用逻辑代码。
在对应的BEGIN和END之间编写代码，例如在/ USER CODE BEGIN 2 /后添加外设初始化后立即执行的代码，在/ USER CODE BEGIN 3 /后添加主循环中需要重复执行的代码。*
![[Pasted image 20251113205629.png]]
#!/usr/bin/bash

openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program build/Release/test4.elf verify reset exit"