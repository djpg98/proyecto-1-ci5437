import sys
import math
import platform

if platform.system() == "Windows":
    newline = "\r\n"
else:
    newline = "\n"

def generate_n_puzzle_stdrep(n):

    with open(f'../n_puzzle/{n}_puzzle_stdrep.psvn', 'w') as psvn_file:

        psvn_file.write(f'DOMAIN Tile {n}' + newline)
        tile_number = n + 1
        domain = 7 * " " + "b " + " ".join([str(i) for i in range(1, tile_number)])
        psvn_file.write(domain + newline)
        psvn_file.write(7 * " " + str(tile_number) + newline)
        psvn_file.write(" ".join(["Tile"] * tile_number) + newline)

        row_length = int(math.sqrt(tile_number))


        for i in range(n + 1):

            up = i - row_length
            down = i + row_length
            left = i - 1
            right = i + 1

            if up >= 0:
                lhs = ["-"] * up + ["X"] + ["-"] * (i - (up + 1)) + ["b"] + ["-"] * (tile_number - (i + 1))
                assert(len(lhs) == tile_number)
                rhs = lhs[:]
                rhs[up], rhs[i] = rhs[i], rhs[up]
                psvn_file.write(" ".join(lhs) + " => " + " ".join(rhs) + " LABEL BLANKUP" + newline)

            if down <= n:
                lhs = ["-"] * i + ["b"] + ["-"] * (down - (i + 1)) + ["X"] + ["-"] * (tile_number - (down + 1))
                assert(len(lhs) == tile_number)
                rhs = lhs[:]
                rhs[down], rhs[i] = rhs[i], rhs[down]
                psvn_file.write(" ".join(lhs) + " => " + " ".join(rhs) + " LABEL BLANKDOWN" + newline)

            if (left % row_length) != row_length - 1:
                lhs = ["-"] * left + ["X"] + ["b"] + ["-"] * (tile_number - (left + 2))
                assert(len(lhs) == tile_number)
                rhs = lhs[:]
                rhs[left], rhs[i] = rhs[i], rhs[left]
                psvn_file.write(" ".join(lhs) + " => " + " ".join(rhs) + " LABEL BLANKLEFT" + newline)

            if (right % row_length) != 0:
                lhs = ["-"] * i + ["b"] + ["X"] + ["-"] * (tile_number - (i + 2))
                assert(len(lhs) == tile_number)
                rhs = lhs[:]
                rhs[right], rhs[i] = rhs[i], rhs[right]
                psvn_file.write(" ".join(lhs) + " => " + " ".join(rhs) + " LABEL BLANKRIGHT" + newline)

        goal = "GOAL " + " ".join([str(i) for i in range(1, tile_number)]) + " b"  
        psvn_file.write(goal + newline)

        psvn_file.close()

try:
    generate_n_puzzle_stdrep(int(sys.argv[1]))
    print(f"El archivo {sys.argv[1]}_puzzle_stdrep.psvn se ha generado en la carpeta ../n_puzzle")
except:
    print("Error: Especifique el tamaño del puzzle")



            



