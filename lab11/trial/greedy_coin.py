import sys

sys.setrecursionlimit(200005)

# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline

def DP_coin_change(N_denom:int, M_amount:int, Denominations:list):
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


def Greedy_coin_change(N_denom:int, M_amount:int, Denominations:list):
    value = M_amount
    num_coin = 0
    for k in range(N_denom):
        max_coin = value//Denominations[k]
        value -= max_coin * Denominations[k]
        num_coin += max_coin

    # but this technically already proves if greeedy is viable or not ...
    if value != 0: return "Impossible"
    return num_coin


def is_valid_for_greedy(N_denom:int, Denominations:tuple)->bool:
    # Check if a greedy approach is applicable
    # Every coin denomination is a multiple of others
    pass


def solve():
    N_denom, M_amount = tuple(map(int, input().split()))
    Denominations = list(map(int, input().split()))
    if is_valid_for_greedy(N_denom, Denominations):
        Denominations.sort(reverse=True) # Descending
        Greedy_coin_change(N_denom, M_amount, Denominations)
    else: DP_coin_change(N_denom, M_amount, Denominations)


if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()

# ------------------------------------------------------------------------------------------------
import sys
from array import array

readline = sys.stdin.buffer.readline

def is_valid_for_greedy(denominations: list[int]) -> bool:
    """
    A greedy solution is guaranteed optimal when the sorted
    denominations form a divisibility chain:

        d[i + 1] % d[i] == 0

    Denominations must be positive and distinct.
    """
    ordered = sorted(denominations)

    if not ordered:
        return False

    if ordered[0] <= 0 or len(set(ordered)) != len(ordered):
        return False

    return all(
        larger % smaller == 0
        for smaller, larger in zip(ordered, ordered[1:])
    )


def greedy_coin_change(amount: int, denominations: list[int]):
    """
    Returns:
        (minimum_coin_count, denomination_counts)

    The returned counts follow the ORIGINAL input order.
        None if the amount cannot be represented.
    """
    counts = [0] * len(denominations)
    remaining = amount

    # Process denominations from largest to smallest.
    order = sorted(
        range(len(denominations)),
        key=denominations.__getitem__,
        reverse=True
    )

    for idx in order:
        counts[idx], remaining = divmod(
            remaining,
            denominations[idx]
        )

    if remaining != 0:
        return None

    return sum(counts), counts



def DP_coin_change(amount: int, denominations: list[int]):
    """
    Unbounded coin change DP.

    Preserves the original implementation's tie-breaking:
      1. Minimize the total number of coins.
      2. Among equally optimal solutions, minimize the
         denomination-count vector lexicographically.

    Returns:
        (minimum_coin_count, denomination_counts)
        None if impossible.
    """

    n = len(denominations)
    INF = amount + 1

    # suffix[i][x] = minimum coins needed to produce x
    # using denominations[i:], i.e. denominations i through n-1.
    #
    # array('q') stores compact signed integer values rather
    # than Python integer objects in ordinary lists.

    suffix = [None] * (n + 1)

    # Base case: no denominations can produce only amount 0.
    suffix[n] = array('q', [INF]) * (amount + 1)
    suffix[n][0] = 0

    # Build the DP table, working backwards through denominations.
    for i in range(n - 1, -1, -1):
        coin = denominations[i]

        # Initially, inherit solutions that do not use this coin.
        current = array('q', suffix[i + 1])

        # Unbounded usage:
        # current[x - coin] already includes the possibility
        # of using this denomination multiple times.
        for value in range(coin, amount + 1):
            candidate = current[value - coin] + 1

            if candidate < current[value]:
                current[value] = candidate

        suffix[i] = current

    min_coins = suffix[0][amount]

    if min_coins == INF:
        return None

    counts = [0] * n

    remaining_amount = amount
    remaining_coins = min_coins

    # Process denominations in their ORIGINAL input order.
    # Prefer the smallest possible count for each denomination.
    for i, coin in enumerate(denominations):
        next_row = suffix[i + 1]

        max_count = remaining_amount // coin

        for count in range(max_count + 1):
            residual = remaining_amount - count * coin

            # Is this count compatible with an optimal solution?
            if (
                next_row[residual] != INF
                and count + next_row[residual] == remaining_coins
            ):
                counts[i] = count

                remaining_amount = residual
                remaining_coins -= count

                break
        else:
            raise RuntimeError("DP reconstruction failed")

    return min_coins, counts

def solve():
    first_line = readline().split()

    if not first_line: return

    N_denom, M_amount = map(int, first_line)
    denominations = list(map(int, readline().split()))

    if (
        len(denominations) != N_denom
        or M_amount < 0
        or any(coin <= 0 for coin in denominations)
    ):
        print(-1)
        return

    if is_valid_for_greedy(denominations):
        result = greedy_coin_change(M_amount, denominations)
    else:
        result = DP_coin_change(M_amount, denominations)

    if result is None:
        print(-1)
        return

    min_coins, counts = result

    print(min_coins)
    print(*counts)