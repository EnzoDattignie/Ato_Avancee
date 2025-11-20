with open("nano_A_B.xyz","r") as file :
    with open("nano_A_B_corrige.xyz","w") as file2 :
        delta = +5
        for lines in file :
            string = lines.split(" ")
            if string[0] == "B" :
                newx = float(string[1])+delta
                file2.write("B "+str(newx)+" "+str(string[2])+" "+str(string[3])+" "+str(string[4])+" "+str(string[5])+" "+str(string[6]))
            else :
                file2.write(lines)
