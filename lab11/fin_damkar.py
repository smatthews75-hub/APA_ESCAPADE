import sys

def greedy_covering(v: list, L: float, R: float) -> int:
    v.sort(key=lambda x: (x[0], -x[1]))
    
    current = L
    events_selected = 0
    idx = 0
    n = len(v)
    eps = 1e-9

    while current < R - eps:
        farthest = current
        
        while idx < n and v[idx][0] <= current + eps:
            if v[idx][1] > farthest:
                farthest = v[idx][1]
            idx += 1
        
        if farthest <= current + eps: return -1
            
        events_selected += 1
        current = farthest

    return events_selected

def solve():
    data = sys.stdin.read().split()
        
    N = int(data[0])
    D = float(data[1])
    
    intervals = []
    pos = 2
    for _ in range(N):
        center = float(data[pos])
        radius = float(data[pos + 1])
        pos += 2

        start = max(0.0, center - radius)
        end = min(D, center + radius)
        if start < end: intervals.append((start, end))

    print(greedy_covering(intervals, 0.0, D))
solve()
