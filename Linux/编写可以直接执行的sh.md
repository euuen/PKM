sh文件不能直接执行一般

有两个关键点
1. 编写`shebang`行
	如：`#!/bin/bash`
2. chmod it
	命令如下：
```sh
chmod +x example.sh
```