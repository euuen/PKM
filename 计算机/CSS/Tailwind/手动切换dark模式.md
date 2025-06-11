Tailwind支持dark模式，这不爽飞了？？

我们需要用js来切换，不过首先设置一下tailwind.config.js，如下：

```ts
module.exports = {
  darkMode: "class", // 关键就是这行
  theme: {
    extend: {},
  },
  plugins: [],
};

```

然后再到tailwind的css里面加上：

```css
@import "tailwindcss";
@custom-variant dark (&:where(.dark, .dark *));
```

如何再js中切换dark主题呢？关键代码如下：

```js
function toggleDarkMode(){
    document.documentElement.classList.toggle("dark");
};
```

只需要调用这个函数就可以切换为dark主题了，再调用这个函数就可以又切换为浅色模式。