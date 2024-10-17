import math
import numpy as np

def loop_data(path):
    data = open(path,'r').read().split(",")
    data.pop()
    data = [float(i) for i in data]
    loop_tiness = (int)(len(data) / 3)
    data1=[0 for i in range(0,loop_tiness)]
    data2=[0 for i in range(0,loop_tiness)]
    data3=[0 for i in range(0,loop_tiness)]
    for i in range(0,loop_tiness):
        data1[i]=data[i*3]
        data2[i]=data[i*3+1]
        data3[i]=data[i*3+2]
    return data1,data2,data3

def epoch_rmse(data):
    predata = [i ** 2 for i in data]
    result = math.sqrt(sum(predata) / len(data))
    return result

def output_data(data_name,data):
    print(data_name)
    print("最小：" + str(np.min(data)))
    print("最大：" + str(np.max(data)))
    print("平均：" + str(np.mean(data)))
    print("中位数：" + str(np.median(data)))
    print("STD：" + str(np.std(data)))
    print("RMSE：" + str(epoch_rmse(data)))
