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