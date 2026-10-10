def print_m(A):
    for row in A:
        for col in row:
            print(col, end=" ")
        print()

def solve():
    n = int(input()) // 2
    C = []
    for _ in range(n): C.append(list(map(int, input().split())))
    # print_m(C)
    # print("===========================")

    for i in range(n): C[i] += list(map(int, input().split()))
    # print_m(C)
    # print("===========================")

    for _ in range(n): C.append(list(map(int, input().split())))
    # print_m(C)
    # print("===========================")

    for i in range(n): C[n + i] += list(map(int, input().split()))
    print_m(C)

    # A11 = []
    # for _ in range(n): A11.append(list(map(int, input().split())))
    # A12 = []
    # for _ in range(n): A12.append(list(map(int, input().split())))
    # A21 = []
    # for _ in range(n): A21.append(list(map(int, input().split())))
    # A22 = []
    # for _ in range(n): A22.append(list(map(int, input().split())))


solve()