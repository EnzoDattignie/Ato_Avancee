import subprocess
import numpy as np 
import matplotlib.pyplot as plt


N = []
repo = "res/"
Files = ["pow0.txt","pow1.txt","pow2.txt","pow3.txt"]
Legendes = ["-O0","-O1","-O2","-O3"]
res = [[],[],[],[]]

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

plt.title("Temps d'exécution de N fonctions pow \navec différents paramètres -Ox")
plt.xlabel("N")
plt.ylabel("Temps(s)")
plt.legend(Legendes)
plt.show()
