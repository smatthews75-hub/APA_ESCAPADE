import sys

class Matrix:
    # __slots__ prevents the creation of a dynamic __dict__ for every instance, 
    # drastically reducing memory overhead and improving attribute access speed.
    __slots__ = ['n', 'data']

    def __init__(self, n, data=None):
        self.n = n
        # Python lists are arrays of pointers, but a pre-allocated 1D list 
        # is the most efficient native structure for contiguous blocks in CPython.
        self.data = data if data is not None else [0] * (n * n)

def add(A:Matrix, B:Matrix):
    # zip() combined with list comprehensions pushes the iteration loop down 
    # into CPython's C implementation, bypassing Python-level loop bytecode.
    return Matrix(A.n, [a + b for a, b in zip(A.data, B.data)])

def sub(A:Matrix, B:Matrix):
    return Matrix(A.n, [a - b for a, b in zip(A.data, B.data)])

def get_submatrix(M:Matrix, row_start:int, col_start:int, size:int):
    subM = Matrix(size)
    M_data = M.data
    sub_data = subM.data
    M_n = M.n
    
    # Bulk slice assignment utilizes C-level memmove under the hood.
    # This completely eliminates nested loop indexing overhead.
    for i in range(size):
        src_start = (row_start + i) * M_n + col_start
        sub_data[i * size : (i + 1) * size] = M_data[src_start : src_start + size]
        
    return subM

def set_submatrix(M:Matrix, subM:Matrix, row_start:int, col_start:int):
    M_data = M.data
    sub_data = subM.data
    M_n = M.n
    size = subM.n
    
    for i in range(size):
        dest_start = (row_start + i) * M_n + col_start
        M_data[dest_start : dest_start + size] = sub_data[i * size : (i + 1) * size]

def multiply_base(A, B):
    n = A.n
    C = Matrix(n)
    A_data = A.data
    B_data = B.data
    C_data = C.data
    
    # Hoisting loop invariants and array references avoids repetitive dictionary lookups
    for i in range(n):
        i_n = i * n
        for k in range(n):
            a_ik = A_data[i_n + k]
            if a_ik == 0:
                continue
            k_n = k * n
            for j in range(n):
                C_data[i_n + j] += a_ik * B_data[k_n + j]
    return C

def strassen(A, B):
    n = A.n
    
    # Python's loop overhead is significantly higher than C++. 
    # The base case cutoff is raised to 64 to delay Strassen's constant-factor penalty.
    if n <= 64:
        return multiply_base(A, B)

    k = n // 2
    
    A11 = get_submatrix(A, 0, 0, k)
    A12 = get_submatrix(A, 0, k, k)
    A21 = get_submatrix(A, k, 0, k)
    A22 = get_submatrix(A, k, k, k)

    B11 = get_submatrix(B, 0, 0, k)
    B12 = get_submatrix(B, 0, k, k)
    B21 = get_submatrix(B, k, 0, k)
    B22 = get_submatrix(B, k, k, k)

    M1 = strassen(add(A11, A22), add(B11, B22))
    M2 = strassen(add(A21, A22), B11)
    M3 = strassen(A11, sub(B12, B22))
    M4 = strassen(A22, sub(B21, B11))
    M5 = strassen(add(A11, A12), B22)
    M6 = strassen(sub(A21, A11), add(B11, B12))
    M7 = strassen(sub(A12, A22), add(B21, B22))

    C11 = add(sub(add(M1, M4), M5), M7)
    C12 = add(M3, M5)
    C21 = add(M2, M4)
    C22 = add(sub(add(M1, M3), M2), M6)

    C = Matrix(n)
    set_submatrix(C, C11, 0, 0)
    set_submatrix(C, C12, 0, k)
    set_submatrix(C, C21, k, 0)
    set_submatrix(C, C22, k, k)
    
    return C

def power(base, exp):
    if exp == 1:
        return base
    
    half = power(base, exp // 2)
    half_sq = strassen(half, half)
    
    if exp % 2 != 0:
        return strassen(half_sq, base)
    return half_sq

def next_power_of_2(n):
    p = 1
    while p < n:
        p *= 2
    return p

def main():
    # Fast I/O read
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    m = int(input_data[1])
    
    padded_n = next_power_of_2(n)
    A = Matrix(padded_n)
    
    idx = 2
    for i in range(n):
        row_offset = i * padded_n
        for j in range(n):
            A.data[row_offset + j] = int(input_data[idx])
            idx += 1

    result_padded = power(A, m)

    # Output extraction
    out = []
    for i in range(n):
        row_start = i * padded_n
        row = [str(result_padded.data[row_start + j]) for j in range(n)]
        out.append(" ".join(row))
    
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    main()