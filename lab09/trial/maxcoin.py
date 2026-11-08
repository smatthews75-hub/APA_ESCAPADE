import sys

sys.setrecursionlimit(200005)

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

def maxcoin_naive(V:tuple[int, ...], N: int):
    if N == 0: return 0
    if N == 1: return max(V[0], 0)
    return max(
        V[N - 1] + maxcoin_naive(V, N - 2),
        maxcoin_naive(V, N - 1)
    )

def maxcoin_topdown(V: tuple[int, ...], N: int):
    memo = [None] * (N + 1)
    memo[0] = 0
    if N >= 1: memo[1] = max(V[0], 0)
    def recursive(k):
        if memo[k] is not None: return memo[k]
        memo[k] = max(
            V[k - 1] + recursive(k - 2),
            recursive(k - 1)
        )
        return memo[k]
    return recursive(N)

def maxcoin_bottomup(V:tuple[int, ...], N:int):
    if N == 0: return 0
    memo = [0] * (N + 1) # memo[0] = 0 base case
    memo[1] = max(V[0], 0) # memo[1] = max of current first step or previous (base case 0)
    for i in range(2, N + 1):
        memo[i] = max(
            V[i - 1] + memo[i - 2], 
            memo[i - 1]
        )
    return memo[N]

def solve():
    V = tuple(map(int, input().split()))
    print(maxcoin_naive(V, len(V)))
    print(maxcoin_topdown(V, len(V)))
    print(maxcoin_bottomup(V, len(V)))

if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()