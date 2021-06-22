import sys
import math
import platform

if platform.system() == "Windows":
    newline = "\r\n"
else:
    newline = "\n"

def break_list_at(mylist, index):

    return (mylist[:index], mylist[index:])

"""
Parameters:
    - n: Number of pieces:
    - k: Number of pieces whose order can be inverted in one action
"""
def top_spin_n_k_stdrep(n, k):

    with open(f'../top-spin/ts_{n}_{k}_stdrep.psvn', 'w') as psvn_file:

        psvn_file.write('#DOMAIN' + newline)
        psvn_file.write(str(n) + newline)
        psvn_file.write(newline)
        psvn_file.write(" ".join(n * [str(n + 1)]) + newline)
        psvn_file.write(newline)

        #spinning_pieces = [f'S{i}' for i in range(1, k + 1)]
        spinning_pieces = ['W', 'X', 'Y', 'Z']
        spinning_pieces_inverted = spinning_pieces[:]
        spinning_pieces_inverted.reverse()

        for i in range(n - k + 1):

            lhs = i * ['-'] + spinning_pieces + (n - i - k) * ['-']
            rhs = i * ['-'] + spinning_pieces_inverted + (n - i - k) * ['-']
            psvn_file.write(" ".join(lhs) + " => " + " ".join(rhs) + newline)

        distance = n - k

        for i in range(n - k + 1, n):

            separated_pieces = break_list_at(spinning_pieces, n - i)
            separated_pieces_inverted = break_list_at(spinning_pieces_inverted, n - i)

            lhs = separated_pieces[1] + distance * ['-'] + separated_pieces[0]
            rhs = separated_pieces_inverted[1] + distance * ['-'] + separated_pieces_inverted[0]
            psvn_file.write(" ".join(lhs) + " => " + " ".join(rhs) + newline)



        psvn_file.write(newline)

        order = [str(i) for i in range(n)]

        for i in range(n):

            segments = break_list_at(order, i)
            new_order = segments[1] + segments[0]
            psvn_file.write("GOAL " + " ".join(new_order) + newline)

try:
    top_spin_n_k_stdrep(int(sys.argv[1]), int(sys.argv[2]))
    print(f"El archivo top-spin/ts_{sys.argv[1]}_{sys.argv[2]}_stdrep.psvn se ha generado en la carpeta ../top-spin")
except:
    print("Error: Especifique argumentos")





