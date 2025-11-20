with open("nano_A_B.xyz","r") as file :
    amax = 0
    bmin = -20
    for lines in file :
        string = lines.split(" ")
        if string[0] == "A" and amax > float(string[1]) :
            amax = float(string[1])
        if string[0] == "B" and float(string[1]) > bmin:
            bmin = float(string[1])
    print(amax, bmin)