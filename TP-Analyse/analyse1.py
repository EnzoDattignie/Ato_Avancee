import numpy as np
import matplotlib.pyplot as plt 


# On commence par lire la donnée

box = np.array([24.7,24.7,24.7])
input = "pos-300K.xyz"

# box = np.array([24.8,24.8,24.8])
# input = "pos-3500K.xyz"


nk = 500
nstep = 1

n_Si = 0
n_O = 0
pos = []

with open(input,"r") as file :
    data = file.readlines()

i = -2
for lines in data :
    if i == -2 :
        n = int(lines.strip())
        pos_temp = np.zeros((n,3))
    if i >= 0 and len(lines.split()) == 4:
        line = lines.split() 
        elmt = line[0]
        pos_temp[i] = [float(line[1]),float(line[2]),float(line[3])]
        if elmt == "Si" :
            n_Si += 1
        if elmt == "O" :
            n_O += 1
    if i >= 0 and len(lines.split()) != 4:
        n_Si = 0
        n_O = 0
        i = -2
        pos.append(np.copy(pos_temp))
    i += 1

print(f"n = {n}, n_O = {n_O}, n_Si = {n_Si}")
print(len(pos))

# print(pos)

#Initialisation des variables
dr = box[0]/(2*nk)
r = np.linspace(0,nk*dr,nk)
h = np.zeros(nk)
g = np.zeros(nk)
rho = n/np.prod(box)
const = 4/3*np.pi*rho

h = np.zeros(nk)
g = np.zeros(nk)

# Calcul du h
for i in range(0,n) :
    for j in range(i+1,n) :
        rij = pos[0][i] - pos[0][j]
        rij -= np.round(rij/box)*box #Permet de respecter les pbc
        rij_sq = 0
        for elmt in rij :
            rij_sq += elmt**2
            k = int(np.floor(np.sqrt(rij_sq)/dr) + 1) #On regarde dans quelle intervalle de distance la particule est
        if (k < nk) :
            h[k] += 2

#normalisation pour g
for k in range(0,nk) :
    g[k] = h[k]/(n*nstep)
    r_low = (k-1)*dr
    r_high = r_low+dr 
    h_id = const*(r_high**3 - r_low**3) #Aire de la surface entre r et r+dr
    g[k] = g[k]/h_id

plt.plot(r,g)
plt.show()