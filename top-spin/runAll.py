import os
import sys

def run_all_cases(solver, cases, pdb, pdbNumber, destination):

    with open(destination, 'w') as outfile:

        outfile.write('value, solution, nodesT, solution, sec' + '\n')

        outfile.close()

    with open(cases, 'r') as all_cases:

        for line in all_cases:

            with open('instance.txt', 'w') as instance:

                instance.write(line)
            
                instance.close()

            os.system(solver + ' instance.txt ' + pdb + ' ' + pdbNumber + ' | tee -a ' + destination)
            #print(solver + ' instance.txt ' + pdb + ' ' + pdbNumber + ' | tee -a ' + destination)

        all_cases.close()

run_all_cases(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])

        

        
