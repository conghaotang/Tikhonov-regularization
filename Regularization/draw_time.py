import matplotlib.pyplot as plt			# 导入模块
import matplotlib
import numpy as np
import math

plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus']=False
plt.rcParams['font.size']=10
plt.rcParams['font.sans-serif']=['Times New Roman']

plt.figure(figsize=(6,4.5),dpi=200)

x_time=[0,10,20,40,60,80,120,150,175,200]

data1 =[
0,0.023692,0.220,	1.526,4.17151,	9.634	,31.403,60.55	,96.3911,142.594
]

data2=[
0,0.002367,0.004	,0.008	,0.011683,0.016	,0.022,0.028,0.033174,0.039
]
plt.plot(x_time, data1, color='red', alpha=0.8, linewidth=2,label="Direct")
plt.plot(x_time, data2, color='blue', alpha=0.8, linewidth=2,label="BTMA")
plt.legend(loc="upper left")
plt.xlabel('Simulation Times (s)')
plt.ylabel('Times (s)')
plt.grid()
plt.savefig("D:\Paper\Paper_2\Fig2.png")
plt.show()
