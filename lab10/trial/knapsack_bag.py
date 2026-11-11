import sys
from functools import lru_cache

sys.setrecursionlimit(200005)

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

def knapsack_topdown_results(
    capacity: int,
    values: list[int],
    weights: list[int]
) -> tuple[int, list[int]]:

    @lru_cache(maxsize=None)
    def recursive(k: int, c: int) -> int:

        if k == 0:
            return 0

        i = k - 1

        skip = recursive(k - 1, c)

        if weights[i] > c:
            return skip

        take = values[i] + recursive(k - 1, c - weights[i])

        return max(take, skip)

    # Calculate the optimal value
    optimal_value = recursive(len(values), capacity)

    # Reconstruct the selected items
    selected = []
    k = len(values)
    c = capacity

    while k > 0:
        i = k - 1

        skip = recursive(k - 1, c)

        if weights[i] <= c:
            take = values[i] + recursive(k - 1, c - weights[i])

            if take > skip:
                selected.append(i)
                c -= weights[i]

        k -= 1

    selected.reverse()

    return optimal_value, selected

def knapsack_topdown(capacity: int, N: int, values: list[int], weights: list[int]):
    # Using lru_cache with primitive integers
    @lru_cache(maxsize=None)
    def recursive(k: int, c: int) -> int:
        # Base case
        if k == 0: return 0
        # convert k currently considered items to 0 indexed 0 to N - 1
        i = k - 1
        # Option 1: do not take the current item
        skip = recursive(k - 1, c)
        # Cannot take the item if it exceeds remaining capacity
        if weights[i] > c: return skip
        # Option 2: take the current item
        take = values[i] + recursive(k - 1, c - weights[i])
        return max(take, skip)

    return recursive(N, capacity)


def knapsack_bottomup(capacity: int, N: int, values: list[int], weights: list[int]) -> int:
    memo = [0] * (capacity + 1) # already has 0 basecase as default value

    for value, weight in zip(values, weights):
        for c in range(capacity, weight - 1, -1):
            candidate = memo[c - weight] + value

            if candidate > memo[c]: memo[c] = candidate

    return memo[capacity]


def solve():
    N = int(input())
    values = tuple(map(int, input().split()))
    weights = tuple(map(int, input().split()))
    capacity = int(input())
    
    print(knapsack_topdown(capacity, N, values, weights))
    print(knapsack_bottomup(capacity, N, values, weights))

'''
8
75 30 600 1000 250 400 800 750
1  2  8   12   4   3   7   6
15
'''

if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()