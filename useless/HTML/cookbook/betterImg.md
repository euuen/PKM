# 更好的图片展示

我发现在Vitepress中直接设置img元素的宽度无法真的改变他的宽度。还好我发现了另一个元素, figure。

下面是示例代码。我相信你能看懂的，而且还能把他投入实践当中。

```html
<div style="display: flex;align-items: center;justify-content: center;gap: 20px;">
    <figure style="width: 100px;">
        <img src="/favicon.ico" alt="">
        <figcaption style="text-align: center;color: #8b8b8b;">最后更新</figcaption>
    </figure>
    <figure style="width: 100px;">
        <img src="/favicon.ico" alt="">
        <figcaption style="text-align: center;color: #8b8b8b;">conda不要喷</figcaption>
    </figure>
    <figure style="width: 100px;">
        <img src="/favicon.ico" alt="">
        <figcaption style="text-align: center;color: #8b8b8b;">miniconda</figcaption>
    </figure>
    <figure style="width: 100px;">
        <img src="/favicon.ico" alt="">
        <figcaption style="text-align: center;color: #8b8b8b;">pyconda</figcaption>
    </figure>
</div>
```
