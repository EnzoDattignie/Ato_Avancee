import numpy as np 
import matplotlib.pyplot as plt 



with open ("test.xyz","r") as file :
    c = 0
    nS = 0
    nO = 0
    for lines in file :
        if c == 0 :
            n = int(lines)
            r = np.zeros((n,3))
        elif c == 1 :
            lines
        else :
            line = lines.split()
            if line[0].strip() == "Si" :
                nS += 1
            else :
                nO += 1
            r[c - 2] = [float(line[1]),float(line[2]),float(line[3])]
        c += 1

box = np.array((24.7,24.7,24.7))
dr = 24.7/500
h = np.zeros(500)

rij = np.zeros(3)
for i in range (0, n-2) :
    for j in range(0,n-1) :
        rij = r[i]-r[j]
        rij = rij - np.round(rij/box)*box
        rij_sq = np.sum(rij**2)
        k = int((rij_sq)**(0.5))
        if (k < n*k):
            h[k] = h[k]+2

plt.plot(np.linspace(0,500*dr,500),h)
plt.show()



