# Electron，好用🥰

## 迅速上手

>2025上半年生效。请注意，就前端这个3天一小该，5天一大该的尿性，这个下载electron的方法很可能在不久的将来会失效。

选择一个你喜欢的目录执行下面的初始化代码

```sh
npm init
```

修改你的package.json。不一定就是照抄

```json{5}
{
  "name": "testElectron",
  "version": "1.0.0",
  "description": "testElectron",
  "main": "main.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "start": "electron ."       // [!code ++]
  },
  "keywords": [],
  "author": "lihuifa",
  "license": "MIT",
}
```

注意高亮与添加的部分。请一定要修改与添加。

接下来，你需要设置镜像，因为我们要下载`Electron`了。见下面的代码。

>不要用pnpm去下，我不知道为什么反正我下不完整，Electron提示我吧node_moduels/electron删了，重新下

```sh
npm config edit
```

然后（在Windows上是这样的），他会弹出来一个记事本，你在空白处写入这两行。

```sh
electron_mirror=https://cdn.npmmirror.com/binaries/electron/
electron_builder_binaries_mirror=https://npmmirror.com/mirrors/electron-builder-binaries/
```

静静等待2min。

>吐槽一下npm这个下载ui。真的很折磨人。都不知道你下到哪里了。就只知道转圈

然后创建一个main.js文件在你的目录里。写如下代码。

```js
const {app, BrowserWindow} = require('electron')

app.on('ready', () => {
    //当app准备好后，执行createWindow创建窗口
    const win = new BrowserWindow({
        width: 800,//窗口宽度
        height: 600,//窗口高度
        autoHideMenuBar: true,//自动隐藏菜单档
        alwaysOnTop: true,//置顶
        x: 500,//窗口位置x坐标
        y: 400//窗口位置y坐标
    })
    //加载一个远程页面
   win.loadUrl("https://cn.bing.com");
})
```

这样你就可以看到一个有bing搜索的窗口被弹出。

恭喜你，成功了。

接下来用html+css+js开心的开发你的ui界面吧！。
