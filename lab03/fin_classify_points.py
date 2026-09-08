def CrossProdCheck(A, B, C):
    cross = (
        (B[0] - A[0]) * (C[1] - A[1])
        - (B[1] - A[1]) * (C[0] - A[0])
    )

    if cross > 0:
        return -1
    elif cross < 0:
        return 1
    else:
        return 0

def ClassifyPoints(points, A, B):
    classification = {}

    for i, P in enumerate(points):
        classification[i] = CrossProdCheck(A, B, P)

    return classification

"""
3
0.0 0.0
10.0 0.0
0.0 1.0
0 -1
1.0 0
"""

N = int(input())
A = tuple(map(float, input().split()))
B = tuple(map(float, input().split()))
points = []
for _ in range(N): points.append(tuple(map(float, input().split())))

left =0
right = 0
mid = 0
for val in ClassifyPoints(points, A, B).values():
    if val == -1: left += 1
    elif val == 1: right += 1
    elif val == 0: mid += 1

print(left, right, mid)
# print(left, end="")
# print(right, end="")
# print(mid)
# C = list(map(float, input().split()))