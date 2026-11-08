import sys

sys.setrecursionlimit(200005)

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

def maximize_happiness(n, happiness):
    # dp[x] = maximum happiness for chocolate length x
    dp = [float('-inf')] * (n + 1)

    # first_piece[x] = length of the first piece in the optimal solution
    first_piece = [None] * (n + 1)

    dp[0] = 0

    # Calculate the optimal solution for every length from 1 to n
    for x in range(1, n + 1):

        # Try every available piece length
        for length, value in happiness:

            if length > x: continue

            candidate = value + dp[x - length]

            if candidate > dp[x]:
                dp[x] = candidate
                first_piece[x] = length

    # Check whether the chocolate can be completely divided
    if dp[n] == float('-inf'):
        return None, []

    # Reconstruct the optimal pieces
    pieces = []
    remaining = n

    while remaining > 0:
        piece = first_piece[remaining]
        pieces.append(piece)
        remaining -= piece

    return dp[n], pieces

def solve():
    n = int(input())
    happiness = []
    happiness.append(tuple(map(int, input().split())))
    happiness.append(tuple(map(int, input().split())))
    happiness.append(tuple(map(int, input().split())))
    print
    (maximize_happiness(n, happiness))

if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()