import math

def generate_increments(n):

    row_len = int(math.sqrt(n + 1))

    line = f"int d0[{n+1}][{n+1}] = " + "{" + ("{" + ", ".join(["2"] * (n + 1)) + "}, ")*(n + 1) + "};"
    print(line)

    for i in range(1, n + 1):
        line =  f"int d{i}[{n+1}][{n+1}] = " + "{"
        contents = []
        i_row = i // row_len
        i_col = i % row_len
        for j in range(n +1):
            j_row = j // row_len
            j_col = j % row_len

            segment = ["2" for i in range(n + 1)]
            segment[j] = "0"
            if j - row_len >= 0:
                segment[j - row_len] = "1" if j_row <= i_row else "-1"

            if j + row_len < n + 1:
                segment[j + row_len] = "1" if j_row >= i_row else "-1"

            if j % row_len != 0:
                segment[j - 1] = "1" if j_col <= i_col else "-1"

            if (j + 1) % row_len != 0:
                segment[j + 1] = "1" if j_col >= i_col else "-1"


            line_segment = "{" + ", ".join(segment) + "}"
            contents.append(line_segment)

        line = line + ", ".join(contents) + "};"
        print(line)

generate_increments(15)


            