N = int(input("N = "))

grid = [[0 for _ in range(N)] for _ in range(N)]

counter = 1

# def print_grid(gr:list) : 
#     for row in grid:
#         for col in row:
#             print(col, end=" ")
#         print()
#     print()

for row in range(N) :
    sub_row = row
    sub_col = 0
    while 0 <= sub_row and sub_col < N:
        grid[sub_row][sub_col] = counter
        # print_grid(grid)
        counter += 1
        sub_row -= 1
        sub_col += 1

for col in range(1, N) :
    sub_row = N - 1
    sub_col = col
    while 0 <= sub_row and sub_col < N:
        grid[sub_row][sub_col] = counter
        # print_grid(grid)
        counter += 1
        sub_row -= 1
        sub_col += 1

for row in grid:
    for col in row:
        print(col, end=" ")
    print()