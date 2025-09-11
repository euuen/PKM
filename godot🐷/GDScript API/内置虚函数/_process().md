# \_process函数

每次帧更新的时候都会调用这个函数。godot会传入此函数一个delta参数，此参数记录了，当前到之前上次运行的时间间隔，以秒为单位。

```python
func _process(delta):
	pass
```