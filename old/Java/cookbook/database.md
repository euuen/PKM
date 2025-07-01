# 数据库

我感觉一般的个人程序，用`sqlite`够了，他算是`MySQL`的一个子集。能用SQL语句，小巧精悍，绝对够用。可惜就是高并发写入性能不行，因为sqlite在同一时间内只予许一个写入操作，其他写入操作要排队。

## 安装`sqlite`

请去Maven的中心仓库找sqlite。名字叫`sqlite-jdbc`，组织是`org.xerial`。复制他的gradle配置。如下：

```md
implementation group: 'org.xerial', name: 'sqlite-jdbc', version: '3.42.0.0'
```

>建议开个代理，或者换gradle源，因为这个包有10多M。

然后运行下面代码看看是否安装成功

```java
public static void main(String[] args) {
    Connection connection = null;
    Statement statement = null;
    try {
        // 加载SQLite驱动程序
        Class.forName("org.sqlite.JDBC");

        // 创建数据库连接
        connection = DriverManager.getConnection("jdbc:sqlite:./hello.db");

        // 创建Statement对象
        statement = connection.createStatement();

        // 创建表
        String createTableSQL = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER)";
        statement.executeUpdate(createTableSQL);

        // 插入数据
        String insertSQL = "INSERT INTO users (name, age) VALUES ('John', 25)";
        statement.executeUpdate(insertSQL);

        System.out.println("inserted successful");
    } catch (ClassNotFoundException e) {
        e.printStackTrace();
    } catch (SQLException e) {
        e.printStackTrace();
    } finally {
        // 关闭Statement和Connection
        if (statement != null) {
            try {
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        if (connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}
```

如果输出了inserted successful就说明成功了。

## 可视化`sqlite`

DB Broswer是一个可是化sqlite的工具。它目前的功能足够满足我们的需求了。[点击此前往官网下载](https://sqlitebrowser.org/dl/)

然后运行它。打开hello.db文件（它在你的Java项目的跟目录下）。

然后查看表users是否多了一个项John 25。这个项即为我们刚刚插入的数据

## SQL语句在sqlite中的使用
