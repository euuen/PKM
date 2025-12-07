# PID演示

```python
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
from collections import deque
import threading
import random

# real time drew line
class RTLine:
    def __init__(self, ax, update_func, style = "r-", update_x_data_func = lambda frame : frame, offset = 0, max_points = 100):
        self.ax = ax
        self.line, = ax.plot([], [], style, linewidth=2)
        self.update_func = update_func
        self.update_x_data_func = update_x_data_func
        self.x_data = deque(maxlen=max_points)
        self.y_data = deque(maxlen=max_points)
        self.frame = 0
        self.offset = offset
        pass
    
    def update(self):
        self.update_y(self.update_func(self.update_x_data_func(self.frame) + self.offset))
        pass
    
    def update_y(self, y):
        self.update_x_y(self.update_x_data_func(self.frame), y)
        pass
    
    def update_x_y(self, x, y):
        self.curr_x = x + self.offset
        self.x_data.append(self.curr_x)
        
        self.curr_y = y
        self.y_data.append(y)
        
        self.frame += 1
        self.line.set_data(self.x_data, self.y_data)
        pass
    
    def set_frame(self, frame):
        self.frame = frame
        pass
    
    def get_curr_x(self):
        return self.curr_x
    
    def get_curr_y(self):
        return self.curr_y
    
    def get_max_x(self):
        return np.max(self.x_data)
        pass
    
    def get_min_x(self):
        return np.min(self.x_data)
        pass

    def get_max_y(self):
        return np.max(self.y_data)
        pass
    
    def get_min_y(self):
        return np.min(self.y_data)
        pass

class RTFig:
    rtlines = []
    update_callback = lambda self : None
    
    def __init__(self):
        self.fig, self.ax = plt.subplots(figsize=(12, 6))
        self.fig.canvas.manager.set_window_title("matplotlib")
        self.ax.grid(True, alpha=0.3)
        self.ax.set_xlabel('s')
        self.ax.set_ylabel('m/s')
        self.ax.set_title('real-time sensor')
        pass
    
    def add_RTline(self, update_func, style = "r-", update_x_data_func = lambda frame : frame, offset = 0, max_points = 100):
        rtline = RTLine(ax=self.ax, update_func=update_func, update_x_data_func=update_x_data_func,style=style, offset=offset, max_points=max_points)
        self.rtlines.append(rtline)
        return rtline
        pass
    
    def set_update_callback(self, callback):
        self.update_callback = lambda : callback()

    def update(self, frame):        
        self.update_callback()
        if len(self.rtlines) == 0:
            return
    
        _ = self.rtlines[0]
        _.update()
        x_min = _.get_min_x()
        x_max = _.get_max_x()
        y_min = _.get_min_y()
        y_max = _.get_max_y()
        for rtline in self.rtlines[1:]:
            rtline.update()
            x_min = min(x_min, rtline.get_min_x())
            x_max = max(x_max, rtline.get_max_x())
            y_min = min(y_min, rtline.get_min_y())
            y_max = max(y_max, rtline.get_max_y())
        
        x_max += 1
        y_min -= 5
        y_max += 5
        
        self.update_ticks(x_min, x_max)
        self.update_y_ticks(y_min, y_max)
            
            
    def show(self):
        self.ani = animation.FuncAnimation(self.fig, lambda frame : self.update(frame), interval=20, blit=False, save_count=50)
        plt.tight_layout()
        plt.show()
        pass
    
    def update_ticks(self, x_min, x_max):
        self.ax.set_xlim(x_min, x_max)
        """智能更新x轴刻度"""
        x_range = x_max - x_min
        
        # 根据x轴范围动态设置刻度间隔
        if x_range <= 20:
            tick_interval = 2
        elif x_range <= 50:
            tick_interval = 5
        elif x_range <= 100:
            tick_interval = 10
        elif x_range <= 200:
            tick_interval = 20
        else:
            tick_interval = 50
        
        # 设置主要刻度
        self.ax.xaxis.set_major_locator(plt.MultipleLocator(tick_interval))
        
        # 添加次要刻度（可选）
        if tick_interval >= 5:
            self.ax.xaxis.set_minor_locator(plt.MultipleLocator(tick_interval/2))
        
        # 设置刻度标签样式
        self.ax.tick_params(axis='x', which='major', labelsize=9)
        self.ax.tick_params(axis='x', which='minor', labelsize=6)

    def update_y_ticks(self, y_min, y_max):
        self.ax.set_ylim(y_min, y_max)
        """智能更新y轴刻度"""
        y_range = y_max - y_min
        
        # 根据y轴范围动态设置刻度间隔
        if y_range <= 2:
            tick_interval = 0.5
        elif y_range <= 5:
            tick_interval = 1
        elif y_range <= 10:
            tick_interval = 2
        else:
            tick_interval = 5
        
        # 设置y轴主要刻度
        self.ax.yaxis.set_major_locator(plt.MultipleLocator(tick_interval))
        
        # 添加y轴次要刻度
        if tick_interval >= 1:
            self.ax.yaxis.set_minor_locator(plt.MultipleLocator(tick_interval/2))
        

class PID:
    def __init__(self):
        self.myfig = RTFig()
        self.time = 0 # s(秒)为单位
        self.curr_v = 0
        self.target_v = 10 # m/s(米)为单位
        self.mass = 20 # 单位为kg
        self.F = 0 # 单位为N
        self.f = 0.1 # 单位为N
        
        self.kp = 5.0  # 比例系数 - 增加响应速度
        self.ki = 0.5  # 积分系数 - 消除稳态误差
        self.kd = 2.0  # 微分系数 - 抑制超调
        
        # PID状态变量
        self.prev_error = 0
        self.integral = 0
        
        self.myfig.add_RTline(lambda x : self.target_v, "b-", update_x_data_func=lambda frame : frame/50)
        self.myfig.add_RTline(lambda x : self.curr_v, "r-", update_x_data_func=lambda frame : frame/50)
        self.myfig.add_RTline(lambda x : self.F, "g-", update_x_data_func=lambda frame : frame/50)
        self.myfig.set_update_callback(lambda : self.update_data())
        pass
    
    def update_data(self):
        # # PID核心公式
        # self.F += (self.target_v - self.curr_v) * 0.2
        
        # # 仿真
        # self.a = (self.F - self.f + random.random()*10) / self.mass  # 加入干扰
        # self.curr_v  += self.a*0.02
        # self.time += 0.02
        
        # 计算误差
        error = self.target_v - self.curr_v
        
        # PID计算
        # 比例项
        P = self.kp * error
        
        # 积分项（带积分限幅防止积分饱和）
        self.integral += error * 0.02
        # 积分限幅
        self.integral = max(min(self.integral, 10), -10)
        I = self.ki * self.integral
        
        # 微分项
        derivative = (error - self.prev_error) / 0.02
        D = self.kd * derivative
        
        # PID输出
        self.F = P + I + D
        
        # 输出限幅（假设最大控制力为50N）
        self.F = max(min(self.F, 50), -10)
        
        # 更新误差记录
        self.prev_error = error
        
        # 物理仿真（加入随机干扰）
        net_force = self.F - self.f + random.random() * 2 - 1  # 减小干扰幅度
        self.a = net_force / self.mass
        self.curr_v += self.a * 0.02
        
        # 速度不能为负（物理约束）
        self.curr_v = max(self.curr_v, 0)
        
        self.time += 0.02
        
        # 显示
        self.myfig.ax.set_title(f"time: {self.time:.2f}s, speed: {self.curr_v:.2f}m/s, error: {error:.2f}m/s")
        
        pass
    
    def run(self):
        self.myfig.show()
        pass
        

if __name__ == "__main__":
    # myfig = RTFig()
    # myfig.add_RTline(lambda x: 1, update_x_data_func=lambda frame : frame/50)
    # myfig.add_RTline(lambda x: np.sin(x) + 1, update_x_data_func=lambda frame : frame/50, style="b-")
    # myfig.add_RTline(lambda x: np.sin(0.1 / (x+1)), style="g-")
    # myfig.add_RTline(lambda x: np.log(0.1*(x+1)), style="y-")
    # myfig.show()
    pid = PID()
    pid.run()
```