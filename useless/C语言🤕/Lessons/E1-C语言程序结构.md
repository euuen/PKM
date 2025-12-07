# E1-C语言程序结构

```c
#include <stdio.h>  // 1. 预处理指令 (Preprocessor Directives)

int main() {        // 2. 主函数 (main function) - 程序入口点
    // 3. 语句 (Statements) 和 表达式 (Expressions)
    printf("Hello, World!\n"); // 函数调用语句
    return 0;                  // 返回语句
}
```

一个最基本的C语言程序如上。

第一个是头文件，这个`#include`是一个预处理命令，发生在编译器预处理阶段。程序的第一行 `#include <stdio.h> `是预处理器指令，告诉 C 编译器在实际编译之前要包含` stdio.h` 文件。

`stdio.h`