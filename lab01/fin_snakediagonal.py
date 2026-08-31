def solve(N, k, grid) :
    diagonals = (2*N) - 1


    # 1 3 6
    # 2 5 8 
    # 4 7 9

    #  1        2              3              2        1
    # (1)   (2  ,  3)   (4  ,  5  ,  6)   (7  ,  8)   (9)
    # 0.0   1.0   0.1   2.0   1.1   0.2   2.1   1.2   2.2
    

    counter = 0
    prev_counter = 0
    for d in range(1, diagonals + 1) :
        increment = d if (d <= N) else diagonals - d + 1
        counter += increment
        limit = counter + 1
        if (prev_counter < k < limit) :
            row = 0
            col = 0
            loc = k - prev_counter - 1
            if (d % 2 == 0) :
                row = (d - 1 if d<=N else N - 1) - loc
                col = (0 if d<=N else d - N) + loc
            else :
                row = (0 if d<=N else d - N) + loc
                col = (d - 1 if d<=N else N - 1) - loc
            # print(row, col)
            grid[row][col] = k
            return
        prev_counter = counter
    return

# solve(int(input()), int(input()))

N = int(input())
grid = [[0 for _ in range(N)] for _ in range(N)]
for i in range(1, N*N + 1):
    solve(N, i, grid)
for row in grid:
    for col in row:
        print(f"{col:<2}", end=" ")
    print()