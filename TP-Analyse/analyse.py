import numpy as np
import matplotlib.pyplot as plt 


# On commence par lire la donnée

box = np.array([24.7,24.7,24.7])
input = "pos-300K.xyz"
output = "res/paire_save_300K_1pt.log"

# box = np.array([24.8,24.8,24.8])
# input = "pos-3500K.xyz"
# output = "res/paire_save_3500K_1pt.log"
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


dr = box[0]/(2*nk)
r = np.linspace(0,nk*dr,nk)
h = np.zeros(nk)
g = np.zeros(nk)
rho = n/np.prod(box)
const = 4/3*np.pi*rho


# =================================================================================================================================================================
#       All Parts
# =================================================================================================================================================================

print("Calculating for all parts ...")


h0 = np.zeros(nk)
g0 = np.zeros(nk)
# Calcul du h
for m in range(0,nstep) :
    for i in range(0,n) :
        for j in range(i+1,n) :
            rij = pos[m][i] - pos[m][j]
            rij -= np.round(rij/box)*box #Permet de respecter les pbc
            rij_sq = 0
            for elmt in rij :
                rij_sq += elmt**2
                k = int(np.floor(np.sqrt(rij_sq)/dr) + 1) #On regarde dans quelle intervalle de distance la particule est
            if (k < nk) :
                h0[k] += 2

#normalisation pour g
for k in range(0,nk) :
    g0[k] = h0[k]/(n*nstep)
    r_low = (k-1)*dr
    r_high = r_low+dr 
    h_id = const*(r_high**3 - r_low**3) #Aire de la surface entre r et r+dr
    g0[k] = g0[k]/h_id

plt.plot(r,g0,label = "All parts")

# =================================================================================================================================================================
#       O-O
# =================================================================================================================================================================

print("Calculating for O-O ...")

h1 = np.zeros(nk)
g1 = np.zeros(nk)

rho = n_O/np.prod(box)
const = 4/3*np.pi*rho
# Calcul du h
for m in range(0,nstep) :
    for i in range(0,n_O) :
        for j in range(i+1,n_O) :
            rij = pos[m][i] - pos[m][j]
            rij -= np.round(rij/box)*box #Permet de respecter les pbc
            rij_sq = 0
            for elmt in rij :
                rij_sq += elmt**2
                k = int(np.floor(np.sqrt(rij_sq)/dr) + 1) #On regarde dans quelle intervalle de distance la particule est
            if (k < nk) :
                h1[k] += 2

#normalisation pour g
for k in range(0,nk) :
    g1[k] = h1[k]/(n_O*nstep)
    r_low = (k-1)*dr
    r_high = r_low+dr 
    h_id = const*(r_high**3 - r_low**3) #Aire de la surface entre r et r+dr
    g1[k] = g1[k]/h_id

plt.plot(r,g1,label = "O-O")

# =================================================================================================================================================================
#       O-Si
# =================================================================================================================================================================

print("Calculating for O-Si ...")

h2 = np.zeros(nk)
g2 = np.zeros(nk)
rho = n_O/np.prod(box)
const = 4/3*np.pi*rho
# Calcul du h
for m in range(0,nstep) :
    for i in range(0,n_O) :
        for j in range(n_O,n) :
            rij = pos[m][i] - pos[m][j]
            rij -= np.round(rij/box)*box #Permet de respecter les pbc
            rij_sq = 0
            for elmt in rij :
                rij_sq += elmt**2
                k = int(np.floor(np.sqrt(rij_sq)/dr) + 1) #On regarde dans quelle intervalle de distance la particule est
            if (k < nk) :
                h2[k] += 2


#normalisation pour g
for k in range(0,nk) :
    g2[k] = h2[k]/(n_O*nstep)
    r_low = (k-1)*dr
    r_high = r_low+dr 
    h_id = const*(r_high**3 - r_low**3) #Aire de la surface entre r et r+dr
    g2[k] = g2[k]/h_id

plt.plot(r,g2,label = "Si-O")

# =================================================================================================================================================================
#       Si-Si
# =================================================================================================================================================================

print("Calculating for Si-Si ...")

h3 = np.zeros(nk)
g3 = np.zeros(nk)
rho = n_Si/np.prod(box)
const = 4/3*np.pi*rho
# Calcul du h
for m in range(0,nstep) :
    for i in range(n_O,n) :
        for j in range(i+1,n) :
            rij = pos[m][i] - pos[m][j]
            rij -= np.round(rij/box)*box #Permet de respecter les pbc
            rij_sq = 0
            for elmt in rij :
                rij_sq += elmt**2
                k = int(np.floor(np.sqrt(rij_sq)/dr) + 1) #On regarde dans quelle intervalle de distance la particule est
            if (k < nk) :
                h3[k] += 2


#normalisation pour g
for k in range(0,nk) :
    g3[k] = h3[k]/(n_Si*nstep)
    r_low = (k-1)*dr
    r_high = r_low+dr 
    h_id = const*(r_high**3 - r_low**3) #Aire de la surface entre r et r+dr
    g3[k] = g3[k]/h_id

plt.plot(r,g3,label = "Si-Si")

with open(output,"w") as file :
    file.write("r h_AllPart g_AllPart h_OO g_OO h_SiO g_SiO h_SiSi g_SiSi\n")
    for i in range(0,len(r)) :
        file.write(f"{r[i]} {h0[i]} {g0[i]} {h1[i]} {g1[i]} {h2[i]} {g2[i]} {h3[i]} {g3[i]}\n")




plt.legend()
plt.show()