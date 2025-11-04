import subprocess
import numpy as np 
import matplotlib.pyplot as plt


N = []
repo = "Lennard/res/"
Files = ["LennardNaif1.txt","Lennard11.txt","Lennard21.txt","LennardFinal1.txt"]
Legendes = ["Version Non Opti","Première Opti","Deuxième Opti","Version Finale"]
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

plt.title("Temps d'exécution de N potentiels \navec différentes optimisations")
plt.xlabel("N")
plt.ylabel("Temps(s)")
plt.legend(Legendes)
plt.show()
