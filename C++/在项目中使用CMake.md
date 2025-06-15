> 这里以Arch Linux上编写C++程序为例子了，因为win的msvc就是依托石🪨。当然你可以用msys2来模拟在Linux上写C++，操作都差不多一样，都是pacman

安装C++ toolchain我就不讲了，网上一堆。我强推用vscode,世界第一编辑器，不接受反驳，吊打CLion。

首先看你CMake的版本
```sh
make --version
```

我的是4.0.3

创建一个CMakeLists.txt文件，在里面写上
```python
cmake_minimum_required (VERSION 4.0)
 
project (learn_cmake)
 
add_executable(program main.cpp)
```


## 例子
```python
cmake_minimum_required (VERSION 4.0)

project (boids)

add_executable(boids main.cpp)

target_link_libraries(boids sfml-graphics)
target_link_libraries(boids sfml-window)
target_link_libraries(boids sfml-system)
```

## 参考资料
1. https://blog.csdn.net/iuu77/article/details/129229361
