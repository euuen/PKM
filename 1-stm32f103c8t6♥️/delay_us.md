# delay_us

## 第一种方式

缺点：uwTick无法更新

```cpp
// 计算每微秒的SysTick计数
#define US_FAC (SystemCoreClock / 1000000)

void delay_us(uint32_t nus, uint32_t milli_us) {
    uint32_t temp;
    uint32_t ticks = nus * US_FAC + (milli_us * US_FAC) / 1000;
    
    // 保存原始SysTick配置
    uint32_t original_ctrl = SysTick->CTRL;
    uint32_t original_load = SysTick->LOAD;
    
    // 禁用SysTick中断（保留使能位）
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    
    // 设置重载值并启动计数器
    SysTick->LOAD = ticks - 1;  // 实际计数 = LOAD + 1
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    
    // 轮询等待计数结束
    do {
        temp = SysTick->CTRL;
    } while ((temp & SysTick_CTRL_ENABLE_Msk) && 
             !(temp & SysTick_CTRL_COUNTFLAG_Msk));
    
    // 停止计数器并恢复原始状态
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->LOAD = original_load;
    SysTick->CTRL = original_ctrl;
}
```

## 第二种方式

优点确保不会影响到依赖于SysTick中断的代码

```cpp
void delay_us(uint32_t us) {
    // 1. 计算需要的总节拍数 (ticks)
    uint32_t ticksNeeded = us * (SystemCoreClock / 1000000);
    
    // 2. 获取初始计数器值并处理重载值
    uint32_t reload = SysTick->LOAD + 1; // 注意：LOAD是重载值，实际计数周期是LOAD+1
    uint32_t startTick = SysTick->VAL;   // 获取开始时计数器的值（递减计数）
    uint32_t totalElapsedTicks = 0;      // 累计经过的节拍数
    
    // 3. 等待循环
    while (totalElapsedTicks < ticksNeeded) {
        uint32_t currentTick = SysTick->VAL;
        
        // 计算自上次读取后经过的节拍数
        // 如果当前值小于等于开始值（未发生重载或发生一次）
        if (currentTick <= startTick) {
            totalElapsedTicks += startTick - currentTick;
        } 
        // 如果当前值大于开始值（发生了重载）
        else {
            totalElapsedTicks += startTick + (reload - currentTick);
        }
        startTick = currentTick;
    }
}
```