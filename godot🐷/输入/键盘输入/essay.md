# 键盘输入

在项目设置那里设置好映射,然后就可以用了

比如

```python
func _process(delta):
	if Input.is_action_pressed("ui_up"):
		velocity = Vector2.UP.rotated(rotation) * speed
```




