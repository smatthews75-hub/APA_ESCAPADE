import sys

input = sys.stdin.readline

def change_coin(N, M, D):
    INF = float('inf')
    memo = [(INF, [0] * N) for _ in range(M + 1)]
    memo[0] = (0, [0] * N)

    for i in range(1, M + 1):
        for coin_idx, coin in enumerate(D):
            if coin > i: 
                continue
            
            prev_coins, prev_res = memo[i - coin]
            if prev_coins == INF: 
                continue
            
            next_coin = prev_coins + 1
            
            result = prev_res[:]
            result[coin_idx] += 1
            
            if (next_coin, result) < memo[i]:
                memo[i] = (next_coin, result)

    if memo[M][0] == INF:
        print(-1)
        return

    min_coins, real_result = memo[M]
    
    print(min_coins)
    print(*real_result)

def solve():
    N, M = tuple(map(int, input().split()))
    coin_Denom = tuple(map(int, input().split()))
    change_coin(N, M, coin_Denom)

if __name__ == '__main__':
    solve()
