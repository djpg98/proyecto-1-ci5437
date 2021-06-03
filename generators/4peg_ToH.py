import sys
import math
import platform

if platform.system() == "Windows":
    newline = "\r\n"
else:
    newline = "\n"

def generate_4peg_ToH_stdrep(n):

    with open(f'../4peg_ToH/{n}_disk_4peg_ToH.psvn', 'w') as psvn_file:

        tile_number = 4 * n 
        psvn_file.write(str(tile_number) + newline)
        psvn_file.write(" ".join(["2"] * tile_number) + newline)

        # ith Disk moveset
        for i in range(1, n+1):
            # from j peg
            for j in range(1, 5):
                # to w/w+1 peg
                for w in range(1, 4):

                    toPeg = w+1 if w>=j else w
                    fromPeg = j

                    lhs, rhs = [], []
                    # for each disk
                    for y in range(1, n+1):
                        # for each peg
                        for z in range(1, 5):
                            lhs += (["1"] if y==i else ["0"]) if (fromPeg==z and y<=i) else (["0"] if (toPeg==z and y<=i) else ["-"]) 
                            rhs += (["1"] if y==i else ["0"]) if (toPeg==z and y<=i) else (["0"] if (fromPeg==z and y<=i) else ["-"]) 

                    label = "  LABEL Disk" + str(i) + "_From" + str(fromPeg) + "_To" + str(toPeg) + newline
                    psvn_file.write(" ".join(lhs) + " => " + " ".join(rhs) + label)
            
        goal = "GOAL "
        for i in range(tile_number):
            goal += "1 " if i%4==0 else "0 "
        psvn_file.write(goal + newline)

        psvn_file.close()

try:
    generate_4peg_ToH_stdrep(int(sys.argv[1]))
    print(f"El archivo {sys.argv[1]}_disk_4peg_ToH.psvn se ha generado en la carpeta ../4peg_ToH")
except IndexError:
    print("Error: Especifique la cantidad de discos.")



            



