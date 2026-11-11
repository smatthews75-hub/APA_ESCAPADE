import sys
from functools import lru_cache

sys.setrecursionlimit(5000000)

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

def knapsack_grouped(capacity: int, N: int, groups: list[list[tuple[int, int]]]):
    @lru_cache(maxsize=None)
    def recursive(idx: int, c: int) -> int:
        # Base case: no more book groups left
        if idx == N: 
            return 0
            
        # Option 1: Skip this entire book group
        best = recursive(idx + 1, c)
        
        # Options 2 & 3: Try all valid purchasing choices within this group
        for weight, value in groups[idx]:
            if weight <= c:
                best = max(best, value + recursive(idx + 1, c - weight))
                
        return best

    return recursive(0, capacity)

def solve():
    N, P = tuple(map(int, input().split()))
    
    # groups[i] = (weight, value)
    groups = []
    
    for _ in range(N):
        single_price, score, stock_quantity, grand_total = tuple(map(int, input().split()))
        
        current_group_options = []
        
        # Choice 1 ANJIOG: Buy between 1 and stock_quantity - 1 individual books
        for count in range(1, stock_quantity):
            current_group_options.append((single_price * count, score * count))
            
        # Choice 2: Buy the wholesale bundle
        current_group_options.append((grand_total, score * stock_quantity))
        
        groups.append(current_group_options)
        
    print(knapsack_grouped(P, N, groups))

solve()


# def knapsack_topdown(capacity: int, N: int, values: list[int], weights: list[int]):
#     # Using lru_cache with primitive integers
#     @lru_cache(maxsize=None)
#     def recursive(k: int, c: int) -> int:
#         # Base case
#         if k == 0: return 0
#         # convert k currently considered items to 0 indexed 0 to N - 1
#         i = k - 1
#         # Option 1: do not take the current item
#         skip = recursive(k - 1, c)
#         # Cannot take the item if it exceeds remaining capacity
#         if weights[i] > c: return skip
#         # Option 2: take the current item
#         take = values[i] + recursive(k - 1, c - weights[i])
#         return max(take, skip)

#     return recursive(N, capacity)

# def solve():
#     N, P = tuple(map(int, input().split()))
#     values = []
#     weights = []
#     for _ in range(N):

#         single_price, score, stock_quantity, grand_total = tuple(map(int, input().split()))
#         # BUY SINGLE BOOKS
#         for i in range(stock_quantity):
#             values.append(score)
#             weights.append(single_price)
#         # BUY THE WHOLE STOCK AT THE PRICE OF grand_total which could be cheaper
#         # BUT ITS SUPPOSED TO BE A CHOICE EITHER :
#         # 1. BUY THE grand_total with score * stock_quantity and DONT BUY ANY OF THE SINGLE BOOKS OR
#         # 2. BUY A COUPLE OF SINGLE BOOKS and DONT BUY THE WHOLE STOCK so buy at most <= stock_quantity - 1
#         # HOW TO DO THIS EFFICIENTLY ?

#         values.append(score * stock_quantity)
#         weights.append(grand_total)

#     print(knapsack_topdown(P, N, values, weights))
        
# solve()