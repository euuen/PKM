对于你的**红外测距+OLED显示**项目，以及绝大多数I2C应用，**请按照下表配置**：

|参数|含义|推荐选择|原因|
|---|---|---|---|
|**I2C Speed Mode**​|通信速度模式|**Standard Mode**​|最稳定，完全满足OLED、传感器需求。|
|**I2C Clock Speed**​|具体时钟频率|**100000**​ Hz|与标准模式对应，是安全标准值。|
|**Clock No Stretch**​|禁止从机延时|**Disabled**​|必须允许从机（OLED）在忙时有请求等待的权利。|
|**Address Length**​|设备地址长度|**7-bit**​|行业通用标准。|
|**Dual Address**​|双从机地址|**Disabled**​|用不上。|
|**Slave Address**​|STM32自身从机地址|**0 (或其他任意值)**​|在单主机系统中不重要。|
|**General Call**​|响应广播地址|**Disabled**​|用不上。|