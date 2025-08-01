# 添加一个目录下所有的源文件到CMake里

命令：
```python
# 把dir_path里面的所有源文件保存到var变量中
aux_source_directory(dir_path VAR)

# 推荐变量全部大写

# 添加依赖到program中
add_executable(program ${VAR})
```