# 基本窗口管理

## 资源管理

## 初始化

::: warning 警告
一定要初始化GLFW，GLFW才可以用!
:::

```cpp
glfwInit();
```

## 清理GLFW

```cpp
glfwTerminate();
```


## 窗口管理

## 窗口参数

```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
```

|参数名称|参数说明|取值说明|
|--------------------------|------------|----|
|GLFW_CONTEXT_VERSION_MAJOR|OpenGL主版本|建议用最新版OpenGL,4。如果你的电脑支持的话|
|GLFW_CONTEXT_VERSION_MINOR|OpenGL副版本|建议用4.3的OpenGL，3|
|GLFW_RESIZABLE|设置窗口是否可以放缩|GL_FALSE表示不可以放缩，反之同理|
|GLFW_OPENGL_PROFILE|表示是启用核心gl功能还是兼容gl功能|GLFW_OPENGL_CORE_PROFILE表示核心gl功能，代表现代OpenGL。GLFW_OPENGL_COMPAT_PROFILE表示兼容模式，可以用旧gl功能|

## 创建窗口

```cpp
GLFWwindow* window_handle = glfwCreateWindow(200, 200, "hello opengl", NULL, NULL);
```

然后，你需要给当前窗口创建OpenGL环境才能使用OpenGL

## 销毁窗口

```cpp
glfwDestroyWindow(window_handle);
```

## 创建OpenGL环境

```cpp
glfwMakeContextCurrent(window_handle);
```

## 收集事件

```cpp
glfwPollEvents();
```

## 判断窗口是否应该关闭

```cpp
glfwWindowShouldClose(window_handle);
```

## 刷新屏幕或交换缓冲区

```cpp
glfwSwapBuffers(window_handle);
```

::: tip
你可以使用这行代码启用垂直同步。（如果你想要更自由地帧率控制，请不要执行它）

```cpp
glfwSwapInterval(1);
```
:::

## 获取事件

### 直接获取按键状态

```cpp
// 直接查询当前的按键情况
glfwGetKey(window_handle, key);
```

|返回值|说明|
|----|----|
|GLFW_PRESSED|按下|
|GLFW_REPEATED|一直按着|
|GLFW_RELEAESED|松开|

### 直接获取鼠标状态

```cpp
glfwGetMouseButton(window_handle, button);
```

|返回值|说明|
|----|----|
|GLFW_PRESSED|按下|
|GLFW_REPEATED|一直按着|
|GLFW_RELEAESED|松开|

### 键盘事件

```cpp
// callback函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

glfwSetKeyCallback(window_handle, key_callback);
```

|action|解释|
|--|--|
|GLFW_PRESSED|按下|
|GLFW_REPEATED|一直按着|
|GLFW_RELEAESED|松开|

### 鼠标事件

```cpp
// 隐藏鼠标
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
glfwSetCursorPosCallback(window, mouse_callback);
```
