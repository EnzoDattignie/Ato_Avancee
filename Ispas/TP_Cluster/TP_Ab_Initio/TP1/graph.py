import matplotlib.pyplot as plt
import numpy as np

Ecut =  [50,60,70,80,90]
E = np.array((-1.12847758,-1.13095863,-1.13245953, -1.13355413, -1.13437640))
d = np.array((0.77276,0.76941,0.76891,0.76897,0.76877))

d = (d-0.742)/0.742


plt.title("Evolution de l'énergie selon Ecut(Ry)")
plt.plot(Ecut,E)
plt.show()

plt.title("Taux d'erreur de la distance selon Ecut(Ry)")
plt.plot(Ecut,d)
plt.show()

#%age d'erreur proche de 3% 