在目录下创建layouts文件夹如果没有的话

然后在此文件夹下面创建`default.vue`，一定要创建这个vue文件。

一个基本的写法是：
```vue
<template>
	<h1>your layouts</p>
	<slot />
</template>
```

注意slot，这个是插槽，必须要制定的啊，要不然内容就不显示了啊啊啊啊啊啊啊啊啊。

如何pages中使用呢？只需要用`NuxtLayout`就好了。

```html
<NuxtLayout>
	<p>hello</p>
</NuxtLayout>
```

这个表示用默认布局。那么如何指定用指定的布局呢？使用`name`属性。比如你有一个layout叫`home`，那么如何使用呢？这样就可以了：

```vue
<NuxtLayout name="home" />
```
