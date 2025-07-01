# 缓冲区

## 缓存区管理对象

VAO，现代OpenGL一个有效的管理缓冲区的工具，可以极大的方便我们管理缓冲区。

你可以这么理解VAO的使用。一个模型（Model）对应一个VAO，其绑定了很多的缓冲区，如什么顶点缓冲区，贴图纹理缓冲区，法线缓冲区等等。只要bind了对应的VAO，OpenGL会自动激活相应的缓冲区。

```cpp
GLunit vao;
glGenVertexArrays(1, &vao);
glBindVertexArray(&vao);
```

## 顶点缓冲区

```cpp
// 创建缓冲区
GLunit vbo;
glGenBuffers(1, &vbo);

// 选中缓冲区
glBindBuffer(GL_ARRAY_BUFFER, &vbo);

// 传入缓冲区数据
glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

// 解除选择缓冲区（可选，不过这是个好习惯）
glBindBuffer(GL_ARRAY_BUFFER, nullptr);
```

## 启用缓冲区

```cpp
glBindBuffer(GL_ARRAY_BUFFER, &vbo);

// 设置缓冲区属性
glVertexAtrribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

// 启用location=0处的缓冲区
glEnableVertexAtrribArray(0);
```
