import sys

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

def chocolate_bottom_up(n, values):
    memo = [0] * (n + 1)

    for cut_length in range(1, n + 1):
        for i in range(1, cut_length + 1):
            memo[cut_length] = max(
                memo[cut_length],
                values[i - 1] + memo[cut_length - i]
            )

    return memo[n]

def solve():
    N = int(input())
    amount = tuple(map(int, input().split()))

    print(chocolate_bottom_up(N, amount))

if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()