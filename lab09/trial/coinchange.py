import sys

sys.setrecursionlimit(200005)

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

def coinchange_topdown(D:tuple[int, ...], k:int):
    INF = k + 1
    memo = [-1] * (k + 1)
    memo[0] = 0

    def dp(amount):
        if memo[amount] != -1:
            return memo[amount]

        best = INF

        for coin in D:
            if amount - coin < 0: continue
            candidate = 1 + dp(amount - coin)

            if candidate < best: best = candidate

        memo[amount] = best
        return memo[amount]

    answer = dp(k)

    return -1 if answer == INF else answer

def coinchange_bottomup(coins, k):
    INF = k + 1

    memo = [INF] * (k + 1)
    memo[0] = 0

    for j in range(1, k + 1):
        for coin in coins:
            new_sum = j - coin
            if new_sum < 0: continue
            memo[j] = min(
                memo[j],
                1 + memo[new_sum]
            )

    answer = memo[k]
    print(memo)
    return -1 if answer == INF else answer

def solve():
    # k amount of money
    k = int(input())
    # D is tuple of coin denomination values
    D = tuple(map(int, input().split()))
    # get least number of coins
    print(coinchange_topdown(D, k))
    print(coinchange_bottomup(D, k))

if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()