import matplotlib.pyplot as plt
import numpy as np

dico = {}
Opti = ["O0","O1","O2","O3","O4","O5"]
Opti2 = np.linspace(0,5,6)
keys = ['addition','division','multiplication','pow']
for elmt in keys :
    dico[elmt] = []

with open("resCompil.txt") as f :
    compteur = -1
    compteur2 = 0
    for lines in f :
        key = keys[compteur2]
        if (compteur >= 0) :
            line = lines.strip().split(";")
            for i in range(1,len(line)):
                line[i] = float(line[i])
            dico[key].append(np.average(line[1:]))
            if compteur == 5:
                compteur = -1
                compteur2 += 1
                
        compteur += 1

for elmt in dico :
    plt.scatter(Opti2,dico[elmt])
    plt.xlabel("Degré d'optimisation")
    plt.ylabel("Temps(s)")
    match elmt :
        case 'addition' :
            plt.title("Graphique représentant le temps de calcul de 1e9 additions selon le degré d'optimisation")
        case 'division' :
            plt.title("Graphique représentant le temps de calcul de 1e9 divisions selon le degré d'optimisation")
        case 'multiplication' :
            plt.title("Graphique représentant le temps de calcul de 1e9 multiplications selon le degré d'optimisation")
        case 'pow' :
            plt.title("Graphique représentant le temps de calcul de 1e9 appels de la fonction pow selon le degré d'optimisation")
    plt.show()



