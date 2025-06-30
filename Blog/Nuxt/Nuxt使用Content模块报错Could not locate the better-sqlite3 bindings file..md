# Nuxt使用Content模块报错Could not locate the better-sqlite3 bindings file.

它表明问题出在 **pnpm 的安全机制**上。pnpm 默认会阻止依赖包执行构建脚本（build scripts），除非你显式批准它们。

#### 批准构建脚本（推荐）

运行以下命令批准 `better-sqlite3` 的构建脚本：

```bash
pnpm approve-builds better-sqlite3
```

然后在交互界面中选择：
1. 使用空格键选中 `better-sqlite3`
2. 按回车确认选择