import sys


# def input(): return sys.stdin.readline().rstrip('\r\n')
input = sys.stdin.readline


import sys

input = sys.stdin.readline

def solve():
    line = input().split()
    if not line:
        return
    n = int(line[0])
    c = float(line[1])

    m = []
    cal = []
    pro = []
    w = []
    ratio = []

    for _ in range(n):
        m_, cal_, pro_, w_ = input().split()
        cal_ = float(cal_)
        pro_ = float(pro_)
        w_ = float(w_)

        m.append(m_)
        cal.append(cal_)
        pro.append(pro_)
        w.append(w_)
        
        if pro_ == 0: ratio.append(float('inf'))
        else: ratio.append(cal_ / pro_)


    order = sorted(range(n), key=lambda x: ratio[x])

    taken = []
    protein = 0.0
    EPS = 1e0

    for i in order:
        if c <= EPS: break

        if cal[i] * w[i] <= c:
            taken.append((i, w[i]))
            c -= cal[i] * w[i]
            protein += w[i] * pro[i]
        else:
            tmp = c / cal[i]
            taken.append((i, tmp))
            c = 0.0
            protein += tmp * pro[i]

    if c > EPS:
        print("MUSTAHIL")
        return

    print(f"{protein:.3f}", len(taken))
    for idx, amount in sorted(taken):
        print(f"{m[idx]} {amount:.3f}")

solve()

# def solve():
#     n, c = list(map(float, input().split()))

#     m = []
#     cal = []
#     pro = []
#     w = []
#     ratio = []

#     for i in range(int(n)):
#         m_, cal_, pro_, w_  = list(map(str, input().split()))
#         m_ = str(m_)
#         cal_ = float(cal_)
#         pro_ = float(pro_)
#         w_ = float(w_)

#         m.append(m_)
#         cal.append(cal_)
#         pro.append(pro_)
#         w.append(w_)
#         ratio.append(cal_ / pro_)
    
#     order = sorted(range(len(m)), key = lambda x: ratio[x])

#     taken = []
#     protein = 0
#     for i in order:
#         if c <= 0: break

#         if cal[i] * w[i] <= c:
#             taken.append((i, w[i]))
#             c -= cal[i] * w[i]
#             protein += w[i] * pro[i]
#         else:
#             tmp = c / cal[i]
#             taken.append((i, tmp))
#             c -= cal[i] * tmp
#             protein += tmp * pro[i]

#     if c < 0:
#         print("MUSTAHIL")
#         return

#     print(f"{protein:.3f}", len(taken))
#     for i in sorted(taken):
#         print(f"{m[i[0]]} {i[1]:.3f}")

# solve()
