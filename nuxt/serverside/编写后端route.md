例子：
```ts
// ./server/routes/hello
export default defineEventHandler(() => 'Hello World!')
```

前端调用`http://localhost:3000/hello`

页面应该就会返回`Hello World!`了。