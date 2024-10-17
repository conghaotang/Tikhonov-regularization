import matplotlib.pyplot as plt			# 导入模块
import matplotlib
import numpy as np
import math
from utils import loop_data,epoch_rmse,output_data

#plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus']=False
plt.rcParams['font.size']=10
plt.rcParams['font.sans-serif']=['Times New Roman']

fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(12, 8),dpi=200)

x_time=np.arange(0,80,0.5)

data1,data2,data3 =loop_data(r'D:\vs项目\Tikhonov_Regularization\result3.txt')
data11,data22,data33 =loop_data(r'D:\vs项目\Tikhonov_Regularization\result4.txt')

ax1.plot(x_time, data1,  color='red', alpha=0.8, linewidth=3, label='Origin')
ax1.plot(x_time, data11,  '--',color='black', alpha=0.8, linewidth=3, label='Reglu')
output_data("原始数据Roll",data1)
output_data("正则化数据Roll",data11)
ax1.set_ylabel('Roll (sec)')
ax1.set_title("Attitude error")
ax1.grid()
ax1.legend(loc='lower right')

ax2.plot(x_time, data2,  color='blue', alpha=0.8, linewidth=3, label='Origin')
ax2.plot(x_time, data22,  '--',color='black', alpha=0.8, linewidth=3, label='Reglu')
output_data("原始数据Pitch",data2)
output_data("正则化数据Pitch",data22)
ax2.set_ylabel('Pitch (sec)')
ax2.grid()
ax2.legend(loc='upper right')

ax3.plot(x_time, data3,  color='green', alpha=0.8, linewidth=3, label='Origin')
ax3.plot(x_time, data33,  '--',color='black', alpha=0.8, linewidth=3, label='Reglu')
output_data("原始数据Yaw",data3)
output_data("正则化数据Yaw",data33)
ax3.set_ylabel('Attitude error (sec)')
ax3.grid()
ax3.legend(loc='upper right')
ax3.set_xlabel('Times (s)')
ax3.set_ylabel('Yaw (sec)')


#plt.savefig("D:\Paper\Paper_2\Fig1.png")
plt.show()

