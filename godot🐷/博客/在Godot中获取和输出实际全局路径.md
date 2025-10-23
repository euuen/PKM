# 在Godot中获取和输出实际全局路径

```python
# 获取res://对应的实际路径
var res_path = ProjectSettings.globalize_path("res://")
print("项目根目录实际路径: ", res_path)

# 获取user://对应的实际路径
var user_path = ProjectSettings.globalize_path("user://")
print("用户数据目录实际路径: ", user_path)
```
