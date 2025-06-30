可以理解为一个跨组建通信的函数把。

## 例子

```ts
const a = useState('foo', () => 'bar');
```

foo是一个状态，后面这个是初始化函数。这里就是把foo赋值为`'bar'`了。

第二次调用`useState('foo', () => 'bar')`时，不会执行初始化函数，而是直接返回foo的ref。

这个a是一个ref，对应foo状态，使用a.value就可以更改foo的值。

在其他的组建中就可以直接用`useState('foo')`来get foo的ref。

你可以封装一下这个函数。

```ts
// useFoo.ts
export default function() {
	useState('foo', () => 'bar');
}
```

