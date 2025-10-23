# linux如何查看一个文件夹内有多少个文件

```sh
find /path/to/directory -type f -name "*.md" | wc -l
```

这段代码的意思就是，查找`/path/to/directory`下，你的md文件数量