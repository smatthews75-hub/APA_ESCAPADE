import sys
from functools import lru_cache

sys.setrecursionlimit(5000000)

def input(): return sys.stdin.readline().rstrip('\r\n')

def floyd_warshall(graph):
    n = len(graph)
    # Floyd-Warshall nigger
    for k in 'AGTC':
        for i in 'AGTC':
            for j in 'AGTC':
                new_dist = graph[i][k] + graph[k][j]
                if new_dist < graph[i][j]: graph[i][j] = new_dist
    return graph

def ED_topdown(source:str, target:str, Ins:int, Del:int, REPLACE:dict):
    M = len(source)
    N = len(target)
    # Using lru_cache with primitive integers
    @lru_cache(maxsize=None)
    def recursive(m, n):
        if m == 0: return n * Ins
        if n == 0: return m * Del
        if source[m - 1] == target[n - 1]:
            return recursive(m - 1, n - 1)
        return min (
            Del + recursive(m - 1, n),
            Ins + recursive(m, n - 1),
            REPLACE[source[m - 1]][target[n - 1]] + recursive(m - 1, n -1)
        )
    return recursive(M, N)

'''
AGT
GTT
1 2
0 5 2 3
5 0 1 2
2 1 0 4
3 2 4 0
'''

def solve():
    SOURCE = input()
    TARGET = input()
    Ins, Del = tuple(map(int, input().split()))
    REPLACE = {
        'A': {'A':0, 'G':0, 'T':0, 'C':0},
        'G': {'A':0, 'G':0, 'T':0, 'C':0},
        'T': {'A':0, 'G':0, 'T':0, 'C':0},
        'C': {'A':0, 'G':0, 'T':0, 'C':0}
    }
    for row in REPLACE.keys():
        values = tuple(map(int, input().split()))
        for idx, col in enumerate(REPLACE[row].keys()):
            REPLACE[row][col] = values[idx]

    REPLACE = floyd_warshall(REPLACE)
    
    # for row in REPLACE.keys():
    #     for col in REPLACE[row].keys():
    #         print(REPLACE[row][col], end=" ")
    #     print()
    
    print(ED_topdown(SOURCE, TARGET, Ins, Del, REPLACE))
    # print(ED_bottomup(SOURCE, TARGET))

solve()