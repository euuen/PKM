# 改变Sence实例的position

例如：

```python
var wengbeng = WengBeng_sence.instantiate()
wengbeng.position = Vector2(0, 0)
add_child(wengbeng)
```

我不知道为什么Godot的自带的编辑器不会智能提示position属性。我一开始还以为没有这个属性呢。果然还是要用C#可能比较好把。GDScript还是太动态了