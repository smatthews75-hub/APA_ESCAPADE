import sys

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

# def DP_bottom_up(N_, A_, options_):
#     first = A_[0]
#     memo = [first] * (N_)
#     for i in range(1, N_):
#         possibilities = [] # 
#         for opt in options_:
#             prev = i - opt
#             if prev < 0: continue
#             possibilities.append(memo[prev]) # dont take current treasure
#             possibilities.append(memo[prev] + A_[i]) # take current treasure
#         if possibilities: memo[i] = max(possibilities)
#     # print(memo)
#     return memo[N_ - 1]

# def DP_bottom_up_req(N_, A_, options_):
#     INF = float('-inf')
#     memo = [INF] * (N_)
#     memo[0] = A_[0]
#     for i in range(N_):
#         if memo[i] == INF: continue
#         possibilities = []
#         for opt in options_:
#             next = i + opt
#             if next >= N_: continue
#             possibilities.append(memo[next] + A_[i]) # take current treasure
#         if possibilities: memo[i] = max(possibilities)

#     # print(memo)
#     return memo[N_ - 1]

def DP_nigger(N_, A_, options_):
    memo = [0] * N_
    for i in range(N_-1, -1, -1):
        best = None
        for opt in options_:
            jump = i + opt
            inc = 0 if jump >= N_ else memo[jump]

            if best is None or inc > best: best = inc
        memo[i] = A_[i] + best
    print(memo[0])


# def aduhampun(N_, pos_, val_, A_, options_):
#     best = float('-inf')

#     def crazy(N, pos, val, treasures, options, best):
#         if pos >= N:
#             # Return the higher value between the current score and the current best
#             return max(val, best)

#         new_val = val + treasures[pos]

#         for jump in options:
#             new_pos = pos + jump
#             # Update best with the result of the recursive path
#             best = crazy(N, new_pos, new_val, treasures, options, best)
            
#             if new_pos >= N: break
                
#         return best # Return the accumulated best score up the stack

#     return crazy(N_, pos_, val_, A_, options_, best)

def solve():
    N, M = tuple(map(int, input().split()))
    treasures = tuple(map(int, input().split()))
    options = tuple(map(int, input().split()))

    # print(aduhampun(N, 0, 0, treasures, options))
    # print(DP_bottom_up(N, treasures, options))
    DP_nigger(N, treasures, options)

solve()