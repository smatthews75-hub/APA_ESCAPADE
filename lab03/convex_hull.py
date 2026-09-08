from math import hypot


def cross(o, a, b):
    return (
        (a[0] - o[0]) * (b[1] - o[1])
        - (a[1] - o[1]) * (b[0] - o[0])
    )


def convex_hull(points):
    # Pair x[i] with y[i].
    # points = sorted(set(zip(x, y)))

    if len(points) <= 1: return 0.0

    lower = []
    for p in points:
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0: lower.pop()
        lower.append(p)

    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0: upper.pop()
        upper.append(p)

    hull = lower[:-1] + upper[:-1]

    perimeter = 0.0

    for i in range(len(hull)):
        x1, y1 = hull[i]
        x2, y2 = hull[(i + 1) % len(hull)]

        perimeter += hypot(x2 - x1, y2 - y1)

    return hull, perimeter

N = int(input())
points = []
for _ in range(N): points.append(tuple(map(int, map(float, input().split()))))
hull, perimeter = convex_hull(points)
print(f"{perimeter:.3f}")
for h in hull:
    print(h[0], h[1])