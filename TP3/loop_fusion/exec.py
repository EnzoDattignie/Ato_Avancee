import subprocess
import numpy as np 
import matplotlib.pyplot as plt


# Init:
samples = 3
cFile = ["loop-fusion-bad","loop-fusion-good"]
# cFile = ["add"]
ext = ".out"
Opt = ["0"]

subprocess.run(["mkdir","out"])
subprocess.run(["mkdir","res"])

N = [1e6]
ndim = np.linspace(100,900,9)

Liste  = []
res = []

#compil
for elmt in cFile : 
    for O in Opt :
        subprocess.run(["gcc","-O"+O,elmt+".c","-o","out/"+elmt+O+ext])
        Liste.append(elmt+O+ext)
        res.append([elmt+O])

for j in range (0,len(res)):
    for i in range (0,len(ndim)) :
        res[j].append([str(ndim[i])])


#mesure
for i in range(0,samples) :
    for j in range (0, len(Liste)) :
        for n in range (0,len(ndim)) :
            subprocess.run(["/usr/bin/time","-o","temp.txt","./out/"+Liste[j],str(N[0]),str(ndim[n])])
            print(["/usr/bin/time","-o","temp.txt","./out/"+Liste[j],str(N[0]),str(ndim[n])])
            with open("./temp.txt") as file :
                i = 0
                for Line in file :
                    if i == 0 :
                        res[j][n+1].append(Line.split(" ")[0].split("u")[0])
                        i = 2



legendes = []
print(len(res))
for i in range (0, len(res)) :
    x = []
    y = []
    for j in range(0,len(res[0][1:])):
        for k in range(0,len(res[i][j+1][1:])) :
            res[i][j+1][k+1] = float(res[i][j+1][k+1])
        x.append(res[i][j+1][0])
        y.append(float(np.mean(res[i][j+1][1:])))
    legendes.append(res[i][0])
    plt.plot(x,y)
    subprocess.run(["rm","res/"+res[i][0]+".txt"])
    subprocess.run(["touch","res/"+res[i][0]+".txt"])
    with open("res/"+res[i][0]+".txt","a") as file :
        for i in range(0,len(x)) :
            file.write(str(x[i])+";"+str(y[i])+"\n")



plt.legend(legendes)
plt.show()