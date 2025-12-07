# 设置icon

一般就这样就好了
（如何public目录下有一个文件是csust.png）

```ts
head: [
    ['link', { rel: 'icon', href: '/csust.png' }],
],
```

但是，如果你设置了base，如`base: "/csust"`，那么这个就要改一下变成

```ts
head: [
    ['link', { rel: 'icon', href: '/csust/csust.png' }],
],
```

