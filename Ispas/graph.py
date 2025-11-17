import numpy as np 
import matplotlib.pyplot as plt

step = []
E = []
x = []
y =[]
z = []
Rcm = []

with open("res/Meas_A.log","r") as file :
    flag = 0
    for Lines in file :
        if flag == 1 :
            step.append(float(Lines.split()[0].strip()))
            E.append(float(Lines.split()[4].strip()))
            Rcm.append(float(Lines.split()[5].strip()))
            x.append(float(Lines.split()[6].strip()))
            y.append(float(Lines.split()[7].strip()))
            z.append(float(Lines.split()[8].strip()))
        flag = 1
plt.title("Evolution de l'énergie selon le temps")
plt.xlabel("pas")
plt.ylabel("E(\u0190)")
plt.plot(step,E)
plt.show()

plt.title("Evolution de la position sur l'axe x selon le temps")
plt.xlabel("pas")
plt.ylabel("x(\u03c3)")
plt.plot(step,x)
plt.show()

plt.title("Evolution du rayon quadratique moyen selon le temps")
plt.xlabel("pas")
plt.ylabel(r"$R_g$"+"(\u03c3)")
plt.plot(step,Rcm)
plt.show()