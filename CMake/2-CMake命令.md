# CMake命令

## 添加链接库

### **target_link_libraries**

命令示例：

```cpp
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
)
```

### **link_libraries**

> [!warning] 不推荐
> 不推荐你在项目中用这个命令直接添加库，因为这会污染cmake的全局变量

命令示例：

```cpp
link_libraries(${OpenCV_LIBS})
```


## 搜索链接库

### **find_package**

命令示例：

```cpp
find_package(OpenCV REQUIRED)
```

这个**REQUIRED**的意思就是必须要找到OpenCV这个库

搜索成功后，就写一个**target_link_libraries**把OpenCV链接到可执行文件

```cpp
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
```

### **find_library**

命令示例：

```cpp
find_library(QUICKJS_LIBRARY
    NAMES quickjs
    PATHS /usr/local/lib/quickjs
    NO_DEFAULT_PATH
)
```

搜索成功后和上面那个差不多直接添加就好了

```cpp
target_link_libraries(${PROJECT_NAME} ${QUICKJS_LIBRARY})
```

### **aux_source_directory**

> [!warning] 注意
> 注意，当源文件名字更改或者添加了新的文件，必须要重新构建一遍cmakelist才会生效
> 
> 此外，这个不能搜索子文件中的文件

命令示例：

```cpp
# 收集当前目录下的所有源文件，并保存到 SRC_LIST 变量中
aux_source_directory(. SRC_LIST)
```

### **file**

现代cpp所推荐的格式

```cpp
# 使用 GLOB 模式匹配当前目录下所有.cpp文件
file(GLOB SRC_LIST "*.cpp")

# 如果需要递归搜索所有子目录，可以使用 GLOB_RECURSE
file(GLOB_RECURSE SRC_LIST "*.cpp")

# 结合CONFIGURE_DEPENDS选项，可以不用自己手动重新构建cmake从而在必要的时候自动添加cpp文件
file(GLOB SRC_LIST CONFIGURE_DEPENDS "*.cpp")
```

> [!warning] 注意
> GLOB_RECURESE可能会把子目录下的文件也添加进去，在某些时候可能你不希望他添加。



