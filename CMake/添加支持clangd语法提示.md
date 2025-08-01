# 添加支持clangd语法提示

确保你已经安装了clangd插件和已经安装了clangd本体。（默认使用vscode）

clangd依赖`compile_commands.json`文件进行代码提示。如果没有这个文件，clangd就会报错没有xxx头文件，虽然编译可以过吧。

好在，这个文件可以用cmake自己生成。只需要这个命令

```python
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
```

然后重启clangd server就不会报错了。