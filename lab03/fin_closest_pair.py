import sys
import math

sys.setrecursionlimit(200005)

def sudo_distance(x1:float, y1:float, x2:float, y2:float):
    # not squared for efficiency purposes
    dx = x1 - x2
    dy = y1 - y2
    return dx*dx + dy*dy

def closest_pair(x_points:list, y_points:list, N:int):
    min_sudo_dist = float('INF')
    min_pairs = []
    for i in range(N - 1):
        for j in range(i + 1, N):
            current_dist = sudo_distance(x_points[i], y_points[i], x_points[j], y_points[j])
            if current_dist < min_sudo_dist:
                min_sudo_dist = current_dist
                min_pairs.clear()
                min_pairs.append((i, j))
            # elif math.isclose(current_dist, min_sudo_dist): min_pairs.append((i, j))
            elif current_dist == min_sudo_dist: min_pairs.append((i, j))
    return math.sqrt(min_sudo_dist), min_pairs

def solve():
    input()
    x_points = list(map(float, input().split()))
    y_points = list(map(float, input().split()))
    N = len(x_points)
    # print(x_points)
    # print(y_points)
    # print(N)
    min_dist, pairs = closest_pair(x_points, y_points, N)

    print(f"{min_dist:.3f}")
    for p in pairs: print(p[0], p[1])

if __name__ == '__main__':
    t = 1
    # t = int(input())
    for _ in range(t):
        solve()