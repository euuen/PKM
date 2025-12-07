# 定义一个最简单的Resource

```python
# 新建脚本文件 my_resource.gd
extends Resource
class_name MyResource

# 导出属性（会在编辑器中显示）
@export var name: String = "默认资源"
@export var value: int = 100
@export var is_active: bool = true
```

# 保存Resource

```python
func save_resource(res: Resource, path: String):
    ResourceSaver.save(res, path)

# 使用示例
var custom_res = MyResource.new()
save_resource(custom_res, "user://save_data/my_data.tres")
```

# 加载Resource

```python
func load_resource(path: String) -> Resource:
    if ResourceLoader.exists(path):
        return ResourceLoader.load(path)
    return null
```























