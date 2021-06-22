import os
import sys

def run_all_cases(solver, cases, pdb, pdbNumber, destination):

    with open(destination, 'w') as outfile:

        outfile.write('value, solution, nodesT, solution, sec' + '\n')

        outfile.close()

    with open(cases, 'r') as all_cases:

        counter = 1

        for line in all_cases:

            print(f'CASO {counter}')
            counter += 1

            with open('instance.txt', 'w') as instance:

                if line[0] == "0":
                    line = "b" + line[1:]
                else:
                    line = line.replace(" 0", " b")

                instance.write(line)
            
                instance.close()

            os.system(solver + ' instance.txt ' + pdb + ' ' + pdbNumber + ' | tee -a ' + destination)
            #print(solver + ' instance.txt ' + pdb + ' ' + pdbNumber + ' | tee -a ' + destination)

        all_cases.close()

def run_all_cases_manhattan(solver, cases, destination):

    with open(destination, 'w') as outfile:

        outfile.write('value, valueF, solution, nodesT, nodesF, solution, sec' + '\n')

        outfile.close()

    with open(cases, 'r') as all_cases:

        counter = 1

        for line in all_cases:

            print(f'CASO {counter}')
            counter += 1

            with open('instance.txt', 'w') as instance:

                if line[0] == "0":
                    line = "b" + line[1:]
                else:
                    line = line.replace(" 0", " b")

                instance.write(line)
            
                instance.close()

            os.system(solver + ' instance.txt ' + ' | tee -a ' + destination)
            #print(solver + ' instance.txt ' + pdb + ' ' + pdbNumber + ' | tee -a ' + destination)

        all_cases.close()

#run_all_cases_manhattan(sys.argv[1], sys.argv[2], sys.argv[3])
run_all_cases(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])

        

        
