# 环境配置

stm32的开发环境配置起来确实有点麻烦，首先，我不是没有考虑过用stm32cubeide，但是我不知道为什么我就是烧录不了到芯片上（我tm一开始还以为我的stm是盗版的，因为比较便宜，后来从非常正规的老店买了一个海外stm，结果还是不行，这个时候我就意识到是stm32cubeide的问题了）所以不得已切换到了vscode + cmake + openocd的开发环境，这是我的开发界面😃。

![[Pasted image 20250812175930.png]]

>（不的不说一下vscode这个界面是真的好看）

为了广大朋友开发方便，我做了一个模板项目，放在了我的github上面，你只需要clone下来，改一改CMakeLists中的相关配置就可以了。**【stm32f103c8t6-cmake-template】** https://github.com/euuen/stm32f103c8t6-cmake-template 