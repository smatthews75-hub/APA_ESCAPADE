import sys

input = sys.stdin.readline

def DP_coin_change(N_denom:int, M_amount:int, Denominations:tuple):
    INF = float('inf')
    memo = [(INF, [0] * N_denom) for _ in range(M_amount + 1)]
    memo[0] = (0, [0] * N_denom)

    for i in range(1, M_amount + 1):
        for coin_idx, coin in enumerate(Denominations):
            if coin > i: continue
            
            prev_coins, prev_res = memo[i - coin]
            if prev_coins == INF: continue
            
            next_coin = prev_coins + 1
            
            result = prev_res[:]
            result[coin_idx] += 1
            
            if (next_coin, result) < memo[i]: memo[i] = (next_coin, result)

    if memo[M_amount][0] == INF:
        print(-1)
        return

    min_coins, real_result = memo[M_amount]
    
    print(min_coins)
    print(*real_result)


def solve():
    N, M = tuple(map(int, input().split()))
    coin_Denom = tuple(map(int, input().split()))
    DP_coin_change(N, M, coin_Denom)

if __name__ == '__main__':
    solve()
