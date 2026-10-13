from math import hypot


def cross(o, a, b):
    return (
        (a[0] - o[0]) * (b[1] - o[1])
        - (a[1] - o[1]) * (b[0] - o[0])
    )


def convex_hull(points):
    # FIX 1: You MUST sort the points for Andrew's Monotone Chain to work.
    # Using set() removes duplicate coordinates which can also break the cross product.
    points = sorted(set(points))

    # FIX 2: Return a tuple to match the unpacking signature in your driver code.
    if len(points) <= 1: return points, 0.0

    lower = []
    for p in points:
        # Your <= 0 logic here is PERFECT for achieving minimal points. 
        # Because the points are sorted, collinear points will be tested consecutively
        # and result in exactly 0, triggering the pop().
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0: 
            lower.pop()
        lower.append(p)

    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0: 
            upper.pop()
        upper.append(p)

    # Exclude the last point of each half because it's the first point of the other half
    hull = lower[:-1] + upper[:-1]

    perimeter = 0.0

    for i in range(len(hull)):
        x1, y1 = hull[i]
        x2, y2 = hull[(i + 1) % len(hull)]

        perimeter += hypot(x2 - x1, y2 - y1)

    return hull, perimeter

if __name__ == "__main__":
    N = int(input())
    points = []
    for _ in range(N): 
        # Note: map(int, map(float, ...)) truncates decimals. 
        # If your coordinates can contain decimals, use `tuple(map(float, input().split()))` instead.
        points.append(tuple(map(int, map(float, input().split()))))
        
    hull, perimeter = convex_hull(points)
    
    print(f"{perimeter:.3f}")
    for h in hull:
        print(h[0], h[1])