# SQL基础

::: tip
sql对大小写不敏感。但是我们默认都写大写。
:::

## 创建表

```sql
CREATE TABLE IF NOT EXISTS [table_name] (
    [column_name] [data_type] [constraint],
    [column_name] [data_type] [constraint],
)
```

::: tip
可以不写IF NOT EXISTS。他的意思我想你应该能看懂吧。
:::

- table_name：即为表名
- column_name：即为列名
- data_type：数据类型
- constraint：列的约束

示例:

```sql
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT, 
    name TEXT, 
    age INTEGER
)
```

此命令的意思如下：创建一个叫`users`的表，此表有三个列。第一列是`id`，可以看到，它是`INTEGER`类型（相当于Java里的int），具有两个约束。其分别是`PRIMARY KEY`（主键），`AUTOINCREMENT`（自增长）。然后是`name`列与`age`列。

关于约束`PRIMARY KEY`，他的意思是主键，每个项的主键是唯一的不重复的。然后是`AUTOINCREMENT`约束，就是自动增长的意思。你可以参考一下excel的第一列。其实sql数据库和excel差不多。

## 插入数据

```sql
INSERT INTO [table_name] ([column1], [column2], ...) VALUES ([value1], [value2], ...)
```

- table_name: 要插入数据的表。
- column1, column2, ...: 要插入数据的列。
- value1, value2, ...: 对应列的值。

示例：

```sql
INSERT INTO users (name, age) VALUES ('John', 25)
```

## 查询数据

