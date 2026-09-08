def selection_sort_asc(A:list):
    N = len(A)
    for j in range(N - 1):
        least = j
        for i in range(j + 1, N):
            if A[i] < A[least]: least = i
        A[j], A[least] = A[least], A[j]
    return A

def selection_sort_desc(A:list):
    N = len(A)
    for j in range(N - 1):
        most = j
        for i in range(j + 1, N):
            if A[i] > A[most]: most = i
        A[j], A[most] = A[most], A[j]
    return A

if __name__ == "__main__":
    from random import randint
    A = [randint(10,99) for _ in range(10)]
    print(A)
    print(selection_sort_asc(A.copy()))
    print(selection_sort_desc(A.copy()))