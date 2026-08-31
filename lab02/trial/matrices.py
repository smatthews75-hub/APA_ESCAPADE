def print_grid(N, grid):
    for row in range(N):
        for col in range(N):
            print(f"{grid[row * N + col]:<2}", end=" ")
        print()


def grid_on2(N, K):
    print("O(n^2) ========")
    grid = [i for i in range(1, N*N + 1)]
    for row in range(N):
        for col in range(N):
            if grid[row * N + col] == K:
                print(row, col)
                return


def grid_on(N, K):
    print("O(n) ==========")
    grid = [i for i in range(1, N*N + 1)]
    for row in range(N):
        if row*N < K < (row+1)*N + 1:
            for col in range(N):
                if grid[row * N + col] == K:
                        print(row, col)
                        return


def grid_ologn(N, K):
    print("O(log n) ======")
    grid = [i for i in range(1, N*N + 1)]

    # Binary search for row
    lo = 0
    hi = N - 1

    while lo <= hi:
        mid = (lo + hi) // 2
        first = grid[mid * N]

        if first == K:
            row = mid
            break
        elif first < K:
            lo = mid + 1
        else:
            hi = mid - 1
    else:
        row = hi

    # Binary search for column
    lo = 0
    hi = N - 1

    while lo <= hi:
        col = (lo + hi) // 2
        value = grid[row * N + col]

        if value == K:
            print(row, col)
            return
        elif value < K:
            lo = col + 1
        else:
            hi = col - 1


def grid_o1(N, K):
    print("O(1) ==========")
    row = (K - 1) // N
    col = K - ((row * N) + 1)
    print(row, col)



def solve(N:int, K:int):

    grid_on2(N, K)
    grid_on(N, K)
    grid_ologn(N, K)
    grid_o1(N, K)

solve(int(input()), int(input()))