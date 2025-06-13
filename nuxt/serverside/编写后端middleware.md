例子：
```ts
// ./server/middleware/log.ts
export default defineEventHandler((event) => {
  console.log('新请求：' + getRequestURL(event))
})
```

```ts
// ./server/middleware/auth.ts
export default defineEventHandler((event) => {
  event.context.auth = { user: 123 }
})
```
