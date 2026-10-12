def strassn(A, B):
    m1 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1])
    m2 = (A[1][0] + A[1][1]) * B[0][0]
    m3 = A[0][0] * (B[0][1] - B[1][1])
    m4 = A[1][1] * (B[1][0] - B[0][0])
    m5 = (A[0][0] + A[0][1]) * B[1][1]
    m6 = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1])
    m7 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1])

    C = [[0, 0], [0, 0]]

    C[0][0] = m1 + m4 - m5 + m7
    C[0][1] = m3 + m5
    C[1][0] = m2 + m4
    C[1][1] = m1 - m2 + m3 + m6

    return C


def split(A, B, n):
    if n == 2:
        return strassn(A, B)

    mid = n // 2

    A11 = [row[:mid] for row in A[:mid]]
    A12 = [row[mid:] for row in A[:mid]]
    A21 = [row[:mid] for row in A[mid:]]
    A22 = [row[mid:] for row in A[mid:]]

    B11 = [row[:mid] for row in B[:mid]]
    B12 = [row[mid:] for row in B[:mid]]
    B21 = [row[:mid] for row in B[mid:]]
    B22 = [row[mid:] for row in B[mid:]]

    def add(X, Y):
        return [[X[i][j] + Y[i][j] for j in range(mid)]
                for i in range(mid)]

    def sub(X, Y):
        return [[X[i][j] - Y[i][j] for j in range(mid)]
                for i in range(mid)]

    M1 = split(add(A11, A22), add(B11, B22), mid)
    M2 = split(add(A21, A22), B11, mid)
    M3 = split(A11, sub(B12, B22), mid)
    M4 = split(A22, sub(B21, B11), mid)
    M5 = split(add(A11, A12), B22, mid)
    M6 = split(sub(A21, A11), add(B11, B12), mid)
    M7 = split(sub(A12, A22), add(B21, B22), mid)

    C11 = add(sub(add(M1, M4), M5), M7)
    C12 = add(M3, M5)
    C21 = add(M2, M4)
    C22 = add(sub(add(M1, M3), M2), M6)

    C = []

    for i in range(mid):
        C.append(C11[i] + C12[i])

    for i in range(mid):
        C.append(C21[i] + C22[i])

    return C


A = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16]
]

B = [
    [16, 15, 14, 13],
    [12, 11, 10, 9],
    [8, 7, 6, 5],
    [4, 3, 2, 1]
]

C = split(A, B, 4)

for row in C:
    print(row)