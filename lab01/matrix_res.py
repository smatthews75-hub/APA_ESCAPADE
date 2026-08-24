def solve(N, k) :
    diagonals = (2*N) - 1
    # print("d :", diagonals)

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
        # print("prev", prev_counter, "| limit", limit,"| now", counter)
        if (prev_counter < k < limit) :
            # print("increment", increment)
            loc = k - prev_counter - 1
            row = (d - 1 if d<=N else N - 1) - loc # WHAT
            col = (0 if d<=N else d - N) + loc

            print(row, col)
            return
        prev_counter = counter
    # print("FAIL")
    return

# solve(int(input()), int(input()))

N = int(input())
for i in range(1, N*N + 1):
    print(f"{i:<2}: ", end="")
    solve(N, i)