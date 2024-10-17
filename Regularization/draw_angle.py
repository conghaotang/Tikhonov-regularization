import matplotlib.pyplot as plt			# 导入模块
import numpy as np
from utils import loop_data,output_data

plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus']=False
plt.rcParams['font.size']=10
plt.rcParams['font.sans-serif']=['Times New Roman']

plt.figure(figsize=(6,4.5),dpi=200)

x_time=np.arange(0.5,80,0.5)

data1,data2,data3 =loop_data(r'D:\vs项目\Tikhonov_Regularization\angle.txt')

plt.plot(x_time, data1, color='red', alpha=0.8, linewidth=2,label="${A}$ = 0.17rad")
plt.plot(x_time, data2, color='blue', alpha=0.8, linewidth=2,label="${A}$ = 0.09rad")
plt.plot(x_time, data3, color='green', alpha=0.8, linewidth=2,label="${A}$ = 0.03rad")
plt.legend(loc="upper right")
plt.xlabel('Simulation Times (s)')
plt.ylabel('Angle Increment (sec)')
plt.grid()
#plt.savefig("D:\Paper\Paper_2\Fig10.png")
plt.show()
