## PARTIALLL

def solveDIAG(N) :
# def solve(N, k) :
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
        print(prev_counter + 1, end=" ")
        prev_counter = counter
    print()

def solve(N, k, COORDS:list) :
# def solve(N, k) :
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
        # DIAGONALS.append(prev_counter + 1)
        if (prev_counter < k < limit) :
            loc = k - prev_counter - 1
            row = (d - 1 if d<=N else N - 1) - loc
            col = (0 if d<=N else d - N) + loc

            COORDS.append((row, col))
            # print(row, col)
            return
        prev_counter = counter
    return

# solve(int(input()), int(input()))

N = int(input())
m = int(input())
coords = []

solveDIAG(N)

for _ in range(m):
    k = int(input())
    solve(N, k, coords)
    # solve(N, k)

for row, col in coords:
    print(row, col)