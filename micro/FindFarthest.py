
def FindFarthest(A:list):
    min_ = A[0]
    max_ = A[0]
    for i in A:
        if i > max_ : max_ = i
        if i < min_ : min_ = i
    return min_, max_

if __name__ == "__main__" : 
    from random import randint
    A = [randint(0, 100) for _ in range(20)]
    print(A)
    min_, max_ = FindFarthest(A)
    print("FindFarthest :", min_, max_)
    print(min(A), max(A))