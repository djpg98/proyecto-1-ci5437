import sys
import math

def calculate(n):

    row_len = int(math.sqrt(n + 1))
    row = ["0"  for i in range(n + 1)]
    line = "unsigned mtable0[" + str(n + 1) + "] = {" + ", ".join(row) + "};"
    print(line)

    for i in range(1, n + 1):
        row = []

        correct_x = (i - 1) // row_len
        correct_y = (i - 1) % row_len
        for j in range(n + 1):

            if i - 1 != j:

                x_coord = j // row_len
                y_coord = j % row_len

                row.append(str(abs(correct_x - x_coord) + abs(correct_y - y_coord)))

                line = "unsigned mtable" +  str(i) + "[" + str(n + 1) + "] = {" + ", ".join(row) + "};"
            else:

                row.append("0")

        print(line)


    names = [f"mtable{i}" for  i in range(n + 1)]
    line = "unsigned * mtable[" + str(n + 1) + "] = {" + ", ".join(names) + "};"
    print(line)


calculate(int(sys.argv[1]))









