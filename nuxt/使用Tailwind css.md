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

然后加VSCode插件[Tailwind CSS IntelliSense](https://marketplace.visualstudio.com/items?itemName=bradlc.vscode-tailwindcss)，这个可以智能提示tailwindcss

然后加一些配置文件到nuxt中：

在根目录下创建文件`tailwind.config.ts`，并写入：

```ts
/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./components/**/*.{js,vue,ts}",
    "./layouts/**/*.vue",
    "./pages/**/*.vue",
    "./plugins/**/*.{js,ts}",
    "./app.vue",
    "./error.vue",
  ],
  theme: {
    extend: {},
  },
  plugins: [],
}
```

然后在创建文件`assets/css/tailwind.css`，写入tailwindcss指令

```css
@tailwind base;
@tailwind components;
@tailwind utilities;
```

然后在nuxt中导入此css

```ts
export default defineNuxtConfig({
  css: ['~/assets/css/tailwind.css'],
})
```

