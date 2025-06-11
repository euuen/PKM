效果图
按之前![[QQ20250611-070828.png]]
按之后![[QQ20250611-070850.png]]

代码如下啊（使用了vue和tailwind）：

```vue
<!-- ToggleSwitch.vue -->
<template>
    <input type="checkbox" class="
    appearance-none
    relative
    w-14
    h-6
    bg-white
    outline-2
    outline-black
    border-black
    rounded-full
    transition
    duration-300
    before:content-['']
    before:absolute
    before:outline-2
    before:outline-black
    before:rounded-full
    before:bg-slate-200
    before:w-6
    before:h-6
    checked:before:left-8
    checked:bg-green-500
    ">
</template>
```