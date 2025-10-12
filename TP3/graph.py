import os
import numpy as np 
import matplotlib.pyplot as plt 


dim = np.linspace(100,600,6)
res = np.zeros(6)
with open("./loop_interchange/bad_dim.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(dim,res,label="bad")

with open("./loop_interchange/good_dim.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(dim,res,label="good")

with open("./loop_interchange/good_dim_O3.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(dim,res,label="good_O3")

with open("./loop_interchange/bad_dim_O3.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(dim,res,label="bad_O3")
plt.legend()

plt.show()

with open("./loop_interchange/good_dim_O3.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(dim,res,label="good_O3")

with open("./loop_interchange/bad_dim_O3.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(dim,res,label="bad_O3")
plt.legend()

plt.show()

iter = [1e3,1e4,1e5,1e6]
res = np.zeros(len(iter))
with open("./loop_interchange/good_iter.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(iter,res,label="good")

with open("./loop_interchange/bad_iter.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(iter,res,label="bad")




plt.legend()
plt.show()

with open("./loop_interchange/good_iter_O3.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(iter,res,label="good_O3")

with open("./loop_interchange/bad_iter_O3.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            res[compteur]=np.mean(data)
        compteur += 1

plt.plot(iter,res,label="bad_O3")
plt.legend()

plt.show()