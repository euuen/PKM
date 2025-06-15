你需要用到`defineEventHandler`这个方法

例子：

```ts
// ./server/api/hello.ts
export default defineEventHandler((event) => {
  return {
    hello: 'world'
  }
})
```

前端调用：

```ts
const { data } = useFetch('/api/hello')
let hello = data.value?.hello
```