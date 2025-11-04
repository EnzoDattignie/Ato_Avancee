import matplotlib.pyplot as plt
import numpy as np

Labels = ["Non opti -O0","Opti -O0","Non opti -O1","Opti -O1","Non opti -O2","Opti -O2"]
Temps = [2.3,1.5,1.216,0.5,1.19,0.427]

X = {"-O0","-O1","-O2"}
Times = {"Non Optimisé":(2.3,1.216,1.19), "Optimisé":(1.5,0.5,0.427)}

x = np.arange(len(X))
width = 0.25
multiplier = 0

fig,ax = plt.subplots(layout='constrained')

for attribute, measurement in Times.items():
    offset = width*multiplier
    rects = ax.bar(x+offset,measurement, width,label=attribute)
    multiplier +=1

ax.set_xticks(x+width/2,("-O0","-O1","-O2"))
ax.set_ylabel("Temps(s)")
ax.legend()
ax.set_title("Temps d'exécution des deux programmes selon l'argument -Ox")

plt.show()