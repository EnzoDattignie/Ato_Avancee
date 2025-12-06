import numpy as np
import matplotlib.pyplot as plt

r = np.zeros(500)
g_AllPart = np.zeros(500)
g_OO = np.zeros(500)
g_SiO = np.zeros(500)
g_SiSi = np.zeros(500)

input = "res/paire_save_3500K_100pt.log"

with open(input,"r") as file :
    lines = file.readlines()

for i in range(0,len(lines[1:])) :
    r[i] = float(lines[i+1].split()[0])
    g_AllPart[i] = float(lines[i+1].split()[2])
    g_OO[i] = float(lines[i+1].split()[4])
    g_SiO[i] = float(lines[i+1].split()[6])
    g_SiSi[i] = float(lines[i+1].split()[8])

plt.plot(r,g_AllPart,label="All Parts")
plt.plot(r,g_OO,label="O-O")
plt.plot(r,g_SiO,label="Si-O")
plt.plot(r,g_SiSi,label="Si-Si")
plt.legend()
plt.xlabel("r (\u03c3)")
plt.ylabel("g(r)")
plt.show()