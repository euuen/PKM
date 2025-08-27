# vscode智能代码提示（LSP）

我的建议是，别用微软官方的shi，速度慢的同时还不准确。所以我的建议是用clangd。
这边也建议你用Linux（我用的是Arch Linux）

首先你需要准备cmake，vscode，以及最重要的clangd

```sh
sudo pacman -S clangd
```

把你的项目用cmake配置好之后，在你的CMakeLists中添加这行代码，让cmake输出编译命令json文件，这个给clangd做依赖分析用的。

```cpp
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
```

然后，如果你的编译器用的不是clangd的话（交叉编译就更加了），如果其他的编译器，那么需要手动设置一下clangd的参数，因为clangd可能会找不到标准库然后报错。

打开设置，知道clangd的参数设置，如图添加下面代码。

![[Pasted image 20250815090205.png]]

```sh
--query-driver=/usr/bin/arm-none-eabi-gcc
```

因为我是交叉编译，所以改成了这个编译器。

自此，你就获得了一个超快反应速度的LSP了！！！