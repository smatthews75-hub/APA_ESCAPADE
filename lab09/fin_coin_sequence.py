import sys

sys.setrecursionlimit(200005)  

input = sys.stdin.readline  

# def max_top_down(N, V):  # FUCK   
#     memo = {}     
#     memo[0] = 0     
#     memo[1] = max(0, V[0])     
#     memo[2] = max(0, V[0], V[1], V[0] + V[1])     
#     memo[3] = max(0, V[0], V[1], V[0] + V[1], V[2], V[0] + V[2], V[1] + V[2])     
    
#     def rec(n):
#         if n in memo: return memo[n]
    
#         res = max(             
#             V[n - 1] + rec(n - 2),              
#             V[n - 1] + V[n - 2] + rec(n - 3),             
#             rec(n - 1)         
#         )         
#         memo[n] = res     
        
#         return res

#     if (N > 3) : return rec(N)     
#     return memo[N]  

def max_bottom_up(N, V):
    if N == 0: return 0
    if N == 1: return max(0, V[0])
    if N == 2: return max(0, V[0], V[1], V[0] + V[1])
    
    dp = [0] * (N + 1)
    dp[0] = 0
    dp[1] = max(0, V[0])
    dp[2] = max(0, V[0], V[1], V[0] + V[1])
    dp[3] = max(0, V[0], V[1], V[0] + V[1], V[2], V[0] + V[2], V[1] + V[2])
    
    for i in range(4, N + 1):
        dp[i] = max(
            V[i - 1] + dp[i - 2],
            V[i - 1] + V[i - 2] + dp[i - 3],
            dp[i - 1]
        )
    return dp[N]


def solve():     
    N = int(input())     
    V = tuple(map(int, input().split()))     
    # print(max_top_down(N, V)) 
    print(max_bottom_up(N, V)) 

if __name__ == '__main__':     
    t = 1     
    for _ in range(t):         
        solve()
