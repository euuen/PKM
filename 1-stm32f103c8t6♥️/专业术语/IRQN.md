# IRQN

IRQN是**中断请求号**（Interrupt Request Number）的缩写。 在STM32中，每个外设或事件都与一个特定的中断请求号相关联。 这些中断请求号用于标识不同的中断源，并在中断控制器中进行管理。 通常，IRQN是一个用来表示中断请求号的宏定义。 例如，在STM32Cube库中，IRQn_Type是一个枚举类型，定义了各种不同的中断请求号，如USART1_IRQn、TIM2_IRQn等。