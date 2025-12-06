import numpy as np
import matplotlib.pyplot as plt

r = np.zeros(500)
g_AllPart = np.zeros(500)
g_OO = np.zeros(500)
g_SiO = np.zeros(500)
g_SiSi = np.zeros(500)
g_AllPart2 = np.zeros(500)
g_OO2 = np.zeros(500)
g_SiO2 = np.zeros(500)
g_SiSi2 = np.zeros(500)

input = "res/paire_save_300K_100pt.log"
input2 = "res/paire_save_3500K_100pt.log"

with open(input,"r") as file :
    lines = file.readlines()


for i in range(0,len(lines[1:])) :
    r[i] = float(lines[i+1].split()[0])
    g_AllPart[i] = float(lines[i+1].split()[2])
    g_OO[i] = float(lines[i+1].split()[4])
    g_SiO[i] = float(lines[i+1].split()[6])
    g_SiSi[i] = float(lines[i+1].split()[8])

with open(input2,"r") as file :
    lines = file.readlines()

for i in range(0,len(lines[1:])) :
    r[i] = float(lines[i+1].split()[0])
    g_AllPart2[i] = float(lines[i+1].split()[2])
    g_OO2[i] = float(lines[i+1].split()[4])
    g_SiO2[i] = float(lines[i+1].split()[6])
    g_SiSi2[i] = float(lines[i+1].split()[8])

plt.plot(r,g_AllPart,label="300K")
plt.plot(r,g_AllPart2,label="3500K")

plt.legend()
plt.xlabel("r (\u03c3)")
plt.ylabel("g(r)")
plt.show()