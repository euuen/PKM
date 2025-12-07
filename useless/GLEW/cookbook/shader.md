# 着色器

一个创建着色器的模板如下

```cpp
// 这个是顶点着色器，你可以换成其他的
GLunit shader = glCreateShader(GL_VERTEX_SHADER);

// 传入着色器代码
glShaderSource(shader, 1, source, nullptr);

// 编译着色器
glCompileShader(shader);
```

其他着色器

|着色器|解释|
|-|-|
|GL_VERTEX_SHADER|顶点着色器|
|GL_FRAGMENT_SHADER|片段着色器|

一般用顶点与片段着色器就够了，除非你追求更完美的画面。

## OpenGL管线程序

```cpp
// 创建管线程序
GLuint program = glCreateProgram();

// 组装管线
glAttachShader(program, shader);

// 链接程序。一定要链接，要不然没法用
glLinkProgram(program);

// 启用管线而不是运行它。
glUseProgram(program);
```
