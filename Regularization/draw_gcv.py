import matplotlib.pyplot as plt			# 导入模块
import matplotlib
import numpy as np
import math

plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus']=False
plt.rcParams['font.size']=10
plt.rcParams['font.sans-serif']=['Times New Roman']

plt.figure(figsize=(6,4.5),dpi=200)

x_time=[(k+1)*1e7 for k in range(0,100)]

data1 =[
40.6967,12.952,7.46945,5.51634,4.65358,4.24937,4.07716,4.0381,4.08294,4.18463,4.32717,4.50056,4.69819,4.91557,5.1495,5.39766,5.65832,5.93015,6.21211,6.50339,6.80332,7.11136,7.42706,7.75004,8.07999,8.41661,8.75968,9.10897,9.46431,9.82553,10.1925,10.565,10.943,
    11.3264,11.715,12.1088,12.5077,12.9115,13.3203,13.7339,14.1522,14.5753,15.003,15.4354,15.8722,16.3135,16.7592,17.2094,17.6638,18.1225,18.5855,19.0527,19.524,19.9994,20.479,20.9625,21.4501,21.9416,22.4371,22.9365,23.4397,23.9468,24.4577,24.9724,25.4908,26.0129,26.5388,27.0683,27.6014,28.1381,28.6784,29.2223,29.7696,30.3205,30.8749,31.4327,31.994,32.5587,33.1267,33.6981,34.2729,34.851,35.4323,36.017,36.6049,37.196,37.7904,38.3879,38.9886,39.5925,40.1995,40.8096,41.4228,42.0391,42.6584,43.2808,43.9062,44.5347,45.1661,45.8004
]

plt.plot(x_time, data1, color='red', alpha=0.8, linewidth=3)
plt.scatter([3*1e7], [7.46945], marker='o', color='blue', s=80, zorder=2,label='Circle')
plt.scatter([7*1e7], [4.0381], marker='o', color='green', s=80, zorder=2,label='Circle')
plt.scatter([23*1e7], [7.42706], marker='o', color='yellow', s=80, zorder=2,label='Circle')

plt.xlabel('μ',fontdict={'fontsize': 14})
plt.ylabel('GCV')
plt.title("Regularisation Parameter")
plt.grid()
plt.savefig("D:\Paper\Paper_2\Fig3.png")
plt.show()
