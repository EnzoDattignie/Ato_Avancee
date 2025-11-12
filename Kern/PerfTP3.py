import matplotlib.pyplot as plt
import numpy as np

Labels = ["-O0","-O1","-O2"]
Temps = [2.3,1.5,1.216,0.5,1.19,0.427]

X = {"-O0","-O1","-O2"}
Times = {"Referenced cache":(2795092637,2655327910,2644458510), "Missed Cache":(247380333,204506153,128004925)}

x = np.arange(len(X))
width = 0.25
multiplier = 0

fig,ax = plt.subplots(layout='constrained')

for attribute, measurement in Times.items():
    offset = width*multiplier
    rects = ax.bar(x+offset,measurement, width,label=attribute)
    multiplier +=1

ax.set_xticks(x+width/2,("-O0","-O1","-O2"))
ax.set_ylabel("Temps(s)")
ax.legend()
ax.set_title("Evolution du cache selon l'argument de compilation")

plt.show()

X = {"-O0","-O1","-O2"}
Times = {"Referenced cache":(2949705,470269,666873), "Missed Cache":(339107,16201,9229)}

x = np.arange(len(X))
width = 0.25
multiplier = 0

fig,ax = plt.subplots(layout='constrained')

for attribute, measurement in Times.items():
    offset = width*multiplier
    rects = ax.bar(x+offset,measurement, width,label=attribute)
    multiplier +=1

ax.set_xticks(x+width/2,("-O0","-O1","-O2"))
ax.set_ylabel("Temps(s)")
ax.legend()
ax.set_title("Evolution du cache selon l'argument de compilation")

plt.show()

X = {"-O0","-O1","-O2"}
Times = {"Referenced cache":(2013683251,2092814387,1868605668), "Missed Cache":(111373113,81135456,105368878)}

x = np.arange(len(X))
width = 0.25
multiplier = 0

fig,ax = plt.subplots(layout='constrained')

for attribute, measurement in Times.items():
    offset = width*multiplier
    rects = ax.bar(x+offset,measurement, width,label=attribute)
    multiplier +=1

ax.set_xticks(x+width/2,("-O0","-O1","-O2"))
ax.set_ylabel("Temps(s)")
ax.legend()
ax.set_title("Evolution du cache selon l'argument de compilation")

plt.show()

X = {"-O0","-O1","-O2"}
Times = {"Referenced cache":(2571904876,1927856609,1264639015), "Missed Cache":(47207122,116889605,9257402)}

x = np.arange(len(X))
width = 0.25
multiplier = 0

fig,ax = plt.subplots(layout='constrained')

for attribute, measurement in Times.items():
    offset = width*multiplier
    rects = ax.bar(x+offset,measurement, width,label=attribute)
    multiplier +=1

ax.set_xticks(x+width/2,("-O0","-O1","-O2"))
ax.set_ylabel("Temps(s)")
ax.legend()
ax.set_title("Evolution du cache selon l'argument de compilation")

plt.show()