def print_m(A):
    for row in A:
        for col in row:
            print(col, end=" ")
        print()

def solve():
    n, k, l = map(int, input().split())
    # kA + lB
    A = []
    for _ in range(n):
        row = list(map(int, input().split()))
        for i in range(n): row[i] = row[i] * k
        # for i in row: i *= k
        A.append(row)
    
    for row in range(n):
        n_row = list(map(int, input().split()))
        for i, col in enumerate(n_row): 
            # col *= l
            A[row][i] += col * l

    print_m(A)

solve()