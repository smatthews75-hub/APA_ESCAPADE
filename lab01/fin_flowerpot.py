from math import gcd
N = int(input())
M = int(input())
print(N - (N // gcd(N, M)))

# N is total flower pots
# decreased by (N / gcd(N,M)) is showered flowerpots