import matplotlib
import matplotlib.pyplot as plt
import numpy as np

res = []

def  moyenne (liste):
    somme = 0
    for elmt in liste :
        somme += elmt
    return somme/len(liste)

with open("TP1_2/res.txt") as f:
    compteur = 0
    for lines in f :
        if compteur > 0 :
            Liste = lines.strip("\n").split(";")[1:]
            for i in range(0,len(Liste)):
                Liste[i]=float(Liste[i])
            moy=moyenne(Liste)
            res.append(moy)
        compteur += 1

Titres = ["addition double","addition entier","division double","division entier","multiplication double","multiplication entier"]

with open("output.csv","w") as f :
    string1=""
    string2=""
    for i in range (0,len(Titres)) :
        string1 += f"{Titres[i]};"
        string2 += f"{res[i]};"
    f.write(string1+"\n")
    f.write(string2)

matplotlib.rcParams.update({'font.size': 30})
plt.title("Temps d'exécution de chaque programme pour 1e9 exécutions")
plt.ylabel("Temps(s)")
plt.bar(Titres,res)
plt.show()