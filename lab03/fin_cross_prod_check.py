def CrossProdCheck(A, B, C):
    cross = (
        (B[0] - A[0]) * (C[1] - A[1])
        - (B[1] - A[1]) * (C[0] - A[0])
    )

    if cross > 0:
        return -1
    elif cross < 0:
        return 1
    else:
        return 0

A = list(map(float, input().split()))
B = list(map(float, input().split()))
C = list(map(float, input().split()))

print(CrossProdCheck(A, B, C))