import os
import numpy as np 
import matplotlib.pyplot as plt 

good = [0,0,0]
bad = [0,0,0]
with open("./loop_fusion/res.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            if compteur == 0 :
                bad[0] = np.mean(data)
            else :
                good[0] = np.mean(data)
        compteur += 1

with open("./loop_fusion/res1.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            if compteur == 0 :
                bad[1] = np.mean(data)
            else :
                good[1] = np.mean(data)
        compteur += 1

with open("./loop_fusion/res2.txt") as file :
    compteur = -1
    for lines in file :
        if compteur >= 0 :
            data = lines.strip().split(";")[1:]
            for i in range (0, len(data)) :
                data[i] = float(data[i])
            if compteur == 0 :
                bad[2] = np.mean(data)
            else :
                good[2] = np.mean(data)
        compteur += 1

print(f"good : {good}\nbad : {bad}")