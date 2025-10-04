import matplotlib.pyplot as plt
import numpy as np

N = np.linspace(1e8,9e8,9)
Add = []
Mult = []
Div = []

def  moyenne (liste):
    somme = 0
    for elmt in liste :
        somme += elmt
    return somme/len(liste)

with open("TP1/res.txt") as f:
    compteur = 0
    for lines in f :
        if compteur > 0 :
            Liste = lines.strip("\n").split(";")[1:]
            for i in range(0,len(Liste)):
                Liste[i]=float(Liste[i])
            moy=moyenne(Liste)
            if compteur > 18 :
                Mult.append(moy)
            elif compteur > 9 :
                Div.append(moy)
            else :
                Add.append(moy)
        compteur += 1
    
        
# print(N)
# print(Add)

plt.title("Temps d'exécution selon le nombre d'opérations")
plt.xlabel("Nombre d'opérations")
plt.ylabel("Temps(s)")
plt.plot(N,Add,label="Additions")
plt.plot(N,Div,label="Divisions")
plt.plot(N,Mult,label="Multiplications")
plt.legend(loc="upper left")
plt.show()