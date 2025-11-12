import subprocess
import numpy as np 
import matplotlib.pyplot as plt


N = []
repo = "res/"
Files = ["add0.txt","div0.txt","mult0.txt"]
Legendes = ["addition","division","multiplication"]
res = [[],[],[]]

def toFloat(string) :
    x = string.split("e")
    return float(x[0])*10**float(x[1])

for i in range(0, len(Files)) :
    with open (repo+Files[i]) as file :
        N = []
        res = []
        for lines in file :
            N.append(toFloat(lines.strip().split(";")[0]))
            res.append(float(lines.strip().split(";")[1]))
        plt.plot(N,res)

plt.title("Temps d'exécution de N opérations élémentaires sur des doubles")
plt.xlabel("N")
plt.ylabel("Temps(s)")
plt.legend(Legendes)
plt.show()
