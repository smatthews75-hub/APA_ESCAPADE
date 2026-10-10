#include <iostream>
#include <vector>

struct Matrix {
    size_t n;
    std::vector<long long> data;

    Matrix(size_t size) : n(size), data(size * size, 0) {}

    // Map 2D indices to the 1D vector structure
    inline long long& operator()(size_t r, size_t c) {
        return data[r * n + c];
    }

    inline long long operator()(size_t r, size_t c) const {
        return data[r * n + c];
    }
};

Matrix add(const Matrix& A, const Matrix& B) {
    Matrix C(A.n);
    for (size_t i = 0; i < A.data.size(); ++i) {
        C.data[i] = A.data[i] + B.data[i];
    }
    return C;
}

Matrix sub(const Matrix& A, const Matrix& B) {
    Matrix C(A.n);
    for (size_t i = 0; i < A.data.size(); ++i) {
        C.data[i] = A.data[i] - B.data[i];
    }
    return C;
}

Matrix get_submatrix(const Matrix& M, size_t row_start, size_t col_start, size_t size) {
    /*
    size
    */
    Matrix subM(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            subM(i, j) = M(row_start + i, col_start + j);
        }
    }
    return subM;
}

void set_submatrix(Matrix& M, const Matrix& subM, size_t row_start, size_t col_start) {
    for (size_t i = 0; i < subM.n; ++i) {
        for (size_t j = 0; j < subM.n; ++j) {
            M(row_start + i, col_start + j) = subM(i, j);
        }
    }
}

Matrix strassen(const Matrix& A, const Matrix& B) {
    size_t n = A.n;
    
    // Base case: Use standard O(N^3) multiplication for matrices <= 32x32
    // Strassen's constant factor overhead makes it slower for small dimensions.
    if (n <= 32) {
        Matrix C(n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t k = 0; k < n; ++k) {
                for (size_t j = 0; j < n; ++j) {
                    C(i, j) += A(i, k) * B(k, j);
                }
            }
        }
        return C;
    }

    size_t k = n / 2;
    Matrix A11 = get_submatrix(A, 0, 0, k);
    Matrix A12 = get_submatrix(A, 0, k, k);
    Matrix A21 = get_submatrix(A, k, 0, k);
    Matrix A22 = get_submatrix(A, k, k, k);

    Matrix B11 = get_submatrix(B, 0, 0, k);
    Matrix B12 = get_submatrix(B, 0, k, k);
    Matrix B21 = get_submatrix(B, k, 0, k);
    Matrix B22 = get_submatrix(B, k, k, k);

    Matrix M1 = strassen(add(A11, A22)  , add(B11, B22));
    Matrix M2 = strassen(add(A21, A22)  , B11);
    Matrix M3 = strassen(A11                 , sub(B12, B22));
    Matrix M4 = strassen(A22                 , sub(B21, B11));
    Matrix M5 = strassen(add(A11, A12)  , B22);
    Matrix M6 = strassen(sub(A21, A11)  , add(B11, B12));
    Matrix M7 = strassen(sub(A12, A22)  , add(B21, B22));

    Matrix C11 = add(sub(add(M1, M4) , M5), M7);
    Matrix C12 = add(M3                     , M5);
    Matrix C21 = add(M2                     , M4);
    Matrix C22 = add(sub(add(M1, M3) , M2), M6);

    Matrix C(n);
    set_submatrix(C, C11, 0, 0);
    set_submatrix(C, C12, 0, k);
    set_submatrix(C, C21, k, 0);
    set_submatrix(C, C22, k, k);
    
    return C;
}

// Recursive matrix exponentiation by constant factor (divide and conquer)
Matrix power(const Matrix& base, long long exp) {
    if (exp == 1) return base;
    
    Matrix half = power(base, exp / 2);
    Matrix half_sq = strassen(half, half);
    
    if (exp % 2 != 0) {
        return strassen(half_sq, base);
    }
    return half_sq;
}

// Find the next power of 2 for Strassen's dimensional requirements
size_t next_power_of_2(size_t n) {
    size_t p = 1;
    while (p < n) p *= 2;
    return p;
}

int main() {
    // Optimize standard I/O operations for competitive programming speeds
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t n;
    long long m;
    if (!(std::cin >> n >> m)) return 0;

    // Strassen's algorithm dictates sizes strictly as powers of 2 for clean halving. 
    // We pad the matrix with zeroes to the right and bottom, up to the next power of 2.
    size_t padded_n = next_power_of_2(n);
    Matrix A(padded_n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cin >> A(i, j);
        }
    }

    Matrix result_padded = power(A, m);

    // Extract and print the actual top-left n x n section, ignoring the zero padding
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << result_padded(i, j) << (j + 1 == n ? "" : " ");
        }
        std::cout << "\n";
    }

    return 0;
}