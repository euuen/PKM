# 定时器中断

![[Pasted image 20251123133031.png]]

随便选择一个tim，然后勾选内部时钟。

填写一下预分频器和自动重装载器，以达到自己想要的中断频率。然后别忘记定义HAL_TIM_PeriodElapsedCallback