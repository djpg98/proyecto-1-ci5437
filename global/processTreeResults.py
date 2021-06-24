import csv
import os
import sys

def results_to_csv(filename):

    with open(filename, 'r') as infile:

        prev = -1
        current = -1

        name, ext = os.path.splitext(filename)

        with open(name + '.csv', 'w') as outfile: 

            outwriter = csv.writer(outfile, delimiter=",")
            outwriter.writerow(['Profundidad', 'Nodos', 'Branching factor'])

            for line in infile:

                if current != -1:
                    prev = current


                depth, nodes = int(line.split()[-1]), int(line.split()[0])
                current = nodes

                if prev != -1:
                    branch = current/prev
                    outwriter.writerow([depth - 1, nodes, branch])


            outfile.close()

        infile.close()

results_to_csv(sys.argv[1])

    





