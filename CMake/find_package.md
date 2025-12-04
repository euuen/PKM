# cmake find_package

我发现用find_package和target_link_libraries就可以完美使用第三方库了，只需要两行就可以了。

我这里用opencv做一个例子

```python
cmake_minimum_required (VERSION 3.27)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)

project (vison)

find_package(OpenCV REQUIRED)

# message(${OpenCV_DIR})

add_executable(vison main.cpp)

target_link_libraries(vison ${OpenCV_LIBS})
```

只需要几行就可以配置opencv环境了，还不需要自己手动添加includes头文件，也不需要自己手动添加各种链接库库的名字