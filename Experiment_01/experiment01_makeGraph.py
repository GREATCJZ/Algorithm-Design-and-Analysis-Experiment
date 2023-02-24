import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

Bubble=[]
with open("Bubble_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Bubble.append(float(line))

Selction=[]
with open("Selection_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Selction.append(float(line))

Insertion=[]
with open("Insertion_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Insertion.append(float(line))

Shell=[]
with open("Shell_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Shell.append(float(line))

Quick=[]
with open("Quick_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Quick.append(float(line))

Merge=[]
with open("Merge_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Merge.append(float(line))

Heap=[]
with open("Heap_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Heap.append(float(line))

Radix=[]
with open("radix_Sort.txt", "r") as f:  # 打开文件
    for line in f.readlines():
        line = line.strip('\n')  #去掉列表中每一个元素的换行符
        Radix.append(float(line))

N=[]
Time_Using=[]
Sort_Method=[]
for i in range(0,len(Bubble)):
    Time_Using.append(Bubble[i])
    Sort_Method.append("Bubble_Sort")
    Time_Using.append(Selction[i])
    Sort_Method.append("Selction_Sort")
    Time_Using.append(Insertion[i])
    Sort_Method.append("Insertion_Sort")
    Time_Using.append(Shell[i])
    Sort_Method.append("Shell_Sort")
    Time_Using.append(Quick[i])
    Sort_Method.append("Quick_Sort")
    Time_Using.append(Merge[i])
    Sort_Method.append("Merge_Sort")
    Time_Using.append(Heap[i])
    Sort_Method.append("Heap_Sort")
    Time_Using.append(Radix[i])
    Sort_Method.append("Radix_Sort")
    N.append(i*200)
    N.append(i * 200)
    N.append(i * 200)
    N.append(i * 200)
    N.append(i * 200)
    N.append(i * 200)
    N.append(i * 200)
    N.append(i * 200)


data=pd.DataFrame(np.transpose(pd.DataFrame([N,Time_Using,Sort_Method])))
data.columns=['N','Time_Using','Sort_Method']
print(data)

sns.lineplot(x='N',y='Time_Using',data=data,hue='Sort_Method')
plt.show()

N1=[]
Time_Using1=[]
Sort_Method1=[]
for i in range(0,len(Bubble)):
    Time_Using1.append(Shell[i])
    Sort_Method1.append("Shell_Sort")
    Time_Using1.append(Quick[i])
    Sort_Method1.append("Quick_Sort")
    Time_Using1.append(Merge[i])
    Sort_Method1.append("Merge_Sort")
    Time_Using1.append(Heap[i])
    Sort_Method1.append("Heap_Sort")
    Time_Using1.append(Radix[i])
    Sort_Method1.append("Radix_Sort")
    N1.append(i * 200)
    N1.append(i * 200)
    N1.append(i * 200)
    N1.append(i * 200)
    N1.append(i * 200)


data1=pd.DataFrame(np.transpose(pd.DataFrame([N1,Time_Using1,Sort_Method1])))
data1.columns=['N','Time_Using','Sort_Method']
print(data1)

sns.lineplot(x='N',y='Time_Using',data=data1,hue='Sort_Method')
plt.show()