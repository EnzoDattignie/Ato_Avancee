import numpy as np 
import matplotlib.pyplot as plt

step = []
x = []
x2 = []

with open("res/Meas_CollisionFast.log","r") as file :
    flag = 0
    for Lines in file :
        if flag == 1 :
            step.append(float(Lines.split()[0].strip()))
            x.append(float(Lines.split()[6].strip()))
            x2.append(float(Lines.split()[10].strip()))
        flag = 1

plt.title("Déplacement des deux particules dans le temps")
plt.xlabel("step")
plt.ylabel("x(\u03c3)")
plt.plot(step,x,label="Particule A")
plt.plot(step,x2,label="Particule B")
plt.legend()
plt.show()

print(f"somme des mi vi = {(x2[1]-x2[0])/(step[1]-step[0])}")
print(f"somme des mi vi = {(x[-1]-x[-2])/(step[-1]-step[-2])+(x2[-1]-x2[-2])/(step[-1]-step[-2])}")
