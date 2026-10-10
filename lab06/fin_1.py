def print_m(A):
    for row in A:
        for col in row:
            print(col, end=" ")
        print()
    print()

def solve():
    n = int(input())
    A = []
    for _ in range(n):
        A.append(list(map(int, input().split())))

    mid = n // 2

    A11 = [row[:mid] for row in A[:mid]]
    A12 = [row[mid:] for row in A[:mid]]
    A21 = [row[:mid] for row in A[mid:]]
    A22 = [row[mid:] for row in A[mid:]]

    print_m(A11)
    print_m(A12)
    print_m(A21)
    print_m(A22)

solve()