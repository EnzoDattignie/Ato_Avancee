import subprocess
import numpy as np 
import matplotlib.pyplot as plt


repo = "res/"
Files = ["loopinterchange-bad0.txt","loopinterchange-good0.txt"]
Legendes = ["Version non optimisée","Version optimisée"]

def toFloat(string) :
    x = string.split("e")
    return float(x[0])*10**float(x[1])

for i in range(0, len(Files)) :
    with open (repo+Files[i]) as file :
        N = []
        res = []
        for lines in file :
            N.append(float(lines.strip().split(";")[0]))
            res.append(float(lines.strip().split(";")[1]))
        plt.plot(N,res)

plt.title("Temps d'exécution pour N exécutions avec\n des tableaux de taille 900x900")
plt.xlabel("N")
plt.ylabel("Temps(s)")
plt.legend(Legendes)
plt.show()
