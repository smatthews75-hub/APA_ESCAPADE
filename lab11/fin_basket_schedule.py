import sys

sys.setrecursionlimit(200005)

def input(): return sys.stdin.readline().rstrip('\r\n')
# input = sys.stdin.readline

def greedy_scheduling(events:tuple):
    events.sort(key = lambda x: (x[2], x[1])) # 2:end first, 1:start tiebreaker

    selected = []
    last_finish = float("-inf")

    for event in events:
        if event[1] >= last_finish:
            selected.append([event[0], event[3]]) # 0:name, 3:input_index 
            last_finish = event[2] # end

    return selected


def solve():
    N_scheds, T_time = tuple(map(int, input().split()))
    schedules = []
    for i in range(N_scheds):
        name, start, duration = input().split()
        start = int(start)
        end = start + int(duration)
        if end > T_time: continue
        schedules.append((name, int(start), end, i))

    results = greedy_scheduling(schedules)

    print(len(results)) # max number of accepted schedules
    # sort by first come first serve aka input_index
    results.sort(key = lambda x : x[1])

    for res in results: print(res[0])

solve()