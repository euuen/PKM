# 为什么选择lwjgl？

因为用cpp对于绝大部分人来说，配置环境可能就太难了。

# 与cpp中的opengl的区别

除了库的初始化方式和cpp中有所不同之外，其他的API几乎和cpp中的GLEW和GLFW保持一致。

其实就是把glewInit的API变成了下面这个而已。

```cpp
import org.lwjgl.opengl.*;
GL.createCapabilities();
```

glfwInit倒是保留了。

如果要保留和在cpp一样的操作，最好就是static import glfw和glfw，如下

```cpp
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL43.*;
```

这个43是代表要使用的OpenGL的版本。一般现在用的是43。

## 参考书籍

1. 《Computer Graphics Programming in OpenGL with C++ 1st Edition》（计算机图像编程（C++ 和OpenGL））
2. 