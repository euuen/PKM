# Godot读取JSON文件

```python
var file = FileAccess.open("/path/to/file.txt", FileAccess.READ)
var content = file.get_as_text()
var json = JSON.new()
file.close()
```