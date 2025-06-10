首先装好tailwind的依赖，然后用nuxi安装nuxt的tailwind插件。

安装tailwind依赖：

```cpp
pnpm install -D tailwindcss postcss autoprefixer
```

通过安装nuxt tailwind插件：

```cpp
pnpm i -D @nuxtjs/tailwindcss
```

然后用nuxi方便地把tailwindcss插件加入到nuxt中

```cpp
npx nuxi@latest module add tailwindcss
```
