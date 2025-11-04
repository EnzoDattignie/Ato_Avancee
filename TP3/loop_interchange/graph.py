import subprocess
import numpy as np 
import matplotlib.pyplot as plt


repo = "res/"
Files = ["loopinterchange-bad1.txt","loopinterchange-good1.txt"]
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

plt.title("Temps d'exécution pour 10000 exécutions de la boucle")
plt.xlabel("Dimension des tableaux")
plt.ylabel("Temps(s)")
plt.legend(Legendes)
plt.show()
