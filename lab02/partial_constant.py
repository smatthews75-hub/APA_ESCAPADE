# PARTIALL

# def solve(N, k, DIAGONALS:list, COORDS:list) :
def solve(N, k) :
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
        increment = d if (d <= N) else diagonals + 1 - d
        counter += increment
        limit = counter + 1
        if (prev_counter < k < limit) :
            # for i_ in range(prev_counter + 1, limit): DIAGONALS.append(i_)
            loc = k - prev_counter - 1
            row = (d - 1 if d<=N else N - 1) - loc
            col = (0 if d<=N else d - N) + loc

            # COORDS.append((row, col))
            print(row, col)
            return
        prev_counter = counter
    return

# solve(int(input()), int(input()))

N = int(input())
m = int(input())
# diagonals = []
# coords = []
for _ in range(m):
    k = int(input())
    # solve(N, k, diagonals, coords)
    solve(N, k)

# for i_ in diagonals:
#     print(i_, end=" ")
# print()

# for row, col in coords:
#     print(row, col)