import subprocess

# Init:
cFile = ["add","div","mult"]
ext = ".out"
Opt = ["0"]

N = [1e7,5e7,1e8,5e8,1e9]
Liste  = []
res = []

#compil
for elmt in cFile :
    for O in Opt :
        subprocess.run(["gcc","-O"+O,elmt+".c","-o",elmt+O+ext])
        Liste.append(elmt+O+ext)
        res.append([elmt+O])

for j in range (0,len(res)):
    for i in range (0,len(N)) :
        res[j].append([str(N[i])])


#mesure
for i in range(0,5) :
    for j in range (0, len(Liste)) :
        for n in range (0,len(N)) :
            subprocess.run(["/usr/bin/time","-o","temp.txt","./"+Liste[j],str(N[n])])
            with open("./temp.txt") as file :
                i = 0
                for Line in file :
                    if i == 0 :
                        res[j][n+1].append(Line.split(" ")[0].split("u")[0])
                        i = 2


print(len(res))
for i in range (0, len(res)) :
    for j in range(0,len(res[0][1:])):
        for k in range(0,len(res[i][j+1][1:])) :
            res[i][j+1][k+1] = float(res[i][j+1][k+1])
        print(f"{res[i][0]} : {res[i][j+1][0]} : {res[i][j+1][1:]}")