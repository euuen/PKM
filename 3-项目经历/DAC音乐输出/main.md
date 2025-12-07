# 使用DAC播放音乐

我这里使用的是stm32f407vet6，这个板子自带dac，所以说这里我是不需要自己手动实现dac输出的，也就是说不需要自己做一个r2r网络了。

> [!info] r2r网格 参考资料
> 1. 【花几分钟理解DAC】 https://www.bilibili.com/video/BV1YAxkewEQe/?share_source=copy_web&vd_source=d8165ccc8db4f797937e2198122cfca4
> 2. 【花几分钟理解R-2R阶梯型DAC】 https://www.bilibili.com/video/BV1DEYje6EfD/?share_source=copy_web&vd_source=d8165ccc8db4f797937e2198122cfca4

我很快就写好了python代码，把wav文件转为原始采样的声音数据，然后把他写入到了c文件中。

很快就用dma+dac就输出了音乐，一开始，我以为是自己弄错了，因为根本没有声音。后面，把喇叭放到耳朵旁边才能勉强听清楚，我也是服了，这个破stm32为什么输出能力这么有限。

后面我自以为是，看了一点运放的视频，就简单的想，既然stm32的输出能力这么有限，那么干脆让我替他输出就好了把！！！所以我当天晚上就设计了一个电压跟随器。

但是还是我想的太简单了，我的pcb画的跟依托shi一样

![[Pasted image 20251204211523.png]]

可以看到，我这个用的是几个电阻加一个lm358实现的小小电压跟随器。这个电路板都没用电容过滤。。。艾。。。且不说这个，其实lm358做这个音频功放其实效果不是很好，因为lm358毕竟还是很垃圾的一个东西的。

后面，我就想，既然用纯功放不行，还不如回归上个世纪的解决方案，用三极管不就好了?

> [!info] 三极管功放 参考资料
> 1. 【三极管制作喇叭功放】 https://channels.weixin.qq.com/finder-preview/pages/feed?entry_card_type=48&comment_scene=39&appid=51&token=cVZMDwgBEAMaIAgEEhwxNzY0ODUxODA2MzkyNjY0MzM3NC85SVRsdUZnIhgIAxIUCAMSECS5Xdm%2FWhmdxAumBIpggMY%3D&entry_scene=51&eid=export%2FUzFfAgtgekIEAQAAAAAAyMIN72dpfgAAAAstQy6ubaLX4KHWvLEZgBPEgoJkYWEfFLuPzNPgMFkNAcU7G-MEO7H9BRIQOe00LvQbZdOI2Q

