import sys
from functools import lru_cache

sys.setrecursionlimit(200005)

def input(): return sys.stdin.readline().rstrip('\r\n')
# input = sys.stdin.readline


def ED_topdown(source:str, target:str):
    M = len(source)
    N = len(target)
    # Using lru_cache with primitive integers
    @lru_cache(maxsize=None)
    def recursive(m, n):
        if m == 0: return n
        if n == 0: return m
        if source[m - 1] == target[n - 1]:
            return recursive(m - 1, n - 1)
        return min (
            1 + recursive(m - 1, n),
            1 + recursive(m, n - 1),
            1 + recursive(m - 1, n -1)
        )
    return recursive(M, N)


def ED_bottomup(source:str, target:str) -> int:
    pass


def solve():
    SOURCE = input()
    TARGET = input()
    
    print(ED_topdown(SOURCE, TARGET))
    # print(ED_bottomup(SOURCE, TARGET))


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