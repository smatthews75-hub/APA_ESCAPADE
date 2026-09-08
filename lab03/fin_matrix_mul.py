m, n, t, q = map(int, input().split())
A = []
B = []
# print(m, n, t, q)

"""
3 2 4 2
2 1
0 9
3 7
3 2 0 1
1 2 9 3
2 0
1 3
"""

for _ in range(m):
    A.append(list(map(int, input().split())))

for _ in range(n):
    B.append(list(map(int, input().split())))

# row1, col1 = map(int, input().split())
# row2, col2 = map(int, input().split())

# print(row1, col1)
# print(row2, col2)
# A_row1 = A[row1]
# B_col1 = [row[col1] for row in B]    

# A_row2 = A[row2]
# B_col2 = [row[col2] for row in B]

# print(A_row1)
# print(B_col1)

# print(A_row2)
# print(B_col2)

def compute(row, col, n):
    A_row = A[row]
    B_col = [row[col] for row in B]
    STR = ""
    res = 0
    for i in range(n):
        res += A_row[i] * B_col[i]
        STR += f"{A_row[i]}*{B_col[i]}+"
    
    return STR[:-1] + f"={res}"

for _ in range(q):
    row, col = map(int, input().split())
    print(compute(row, col, n))

# string1 = ""
# string2 = ""
# res1 = 0
# res2 = 0
# for i in range(n):
#     res1 += A_row1[i] * B_col1[i]
#     res2 += A_row2[i] * B_col2[i]
#     string1 += f"{A_row1[i]}*{B_col1[i]}+"
#     string2 += f"{A_row2[i]}*{B_col2[i]}+"

# string1 = string1[:-1] + f"={res1}"
# string2 = string2[:-1] + f"={res2}"
# print(string1)
# print(string2)