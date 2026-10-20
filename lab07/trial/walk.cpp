
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

using int64 = long long;
using uint64 = uint64_t;

constexpr int64 MOD = 1'000'000'007LL;

struct Matrix {
    size_t n;
    vector<int64> data;

    explicit Matrix(size_t size)
        : n(size), data(size * size, 0) {}

    int64& operator()(size_t r, size_t c) {
        return data[r * n + c];
    }

    int64 operator()(size_t r, size_t c) const {
        return data[r * n + c];
    }
};

// Standard matrix multiplication: C = A * B (mod MOD).
Matrix multiply(const Matrix& A, const Matrix& B) {
    size_t n = A.n;
    Matrix C(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t k = 0; k < n; ++k) {
            int64 x = A(i, k);

            if (x == 0) continue;

            for (size_t j = 0; j < n; ++j) {
                int64 y = B(k, j);

                if (y == 0) continue;

                C(i, j) = (C(i, j) + x * y) % MOD;
            }
        }
    }

    return C;
}

// Multiply a row vector by a matrix: result = v * A (mod MOD).
vector<int64> multiply_row(
    const vector<int64>& v,
    const Matrix& A
) {
    size_t n = A.n;
    vector<int64> result(n, 0);

    for (size_t i = 0; i < n; ++i) {
        if (v[i] == 0) continue;

        for (size_t j = 0; j < n; ++j) {
            int64 x = A(i, j);

            if (x == 0) continue;

            result[j] = (result[j] + v[i] * x) % MOD;
        }
    }

    return result;
}

// Count walks from source to target using exactly k edges.
int64 count_walks(
    Matrix A,
    uint64 k,
    size_t source,
    size_t target
) {
    size_t n = A.n;

    // Initially, v = e_source^T.
    vector<int64> v(n, 0);
    v[source] = 1;

    while (k > 0) {
        // If this exponent bit is set, apply A^(2^bit).
        if (k & 1ULL) {
            v = multiply_row(v, A);
        }

        k >>= 1;

        // Prepare the next power only if more bits remain.
        if (k > 0) {
            A = multiply(A, A);
        }
    }

    return v[target];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input:
    // n m k source target
    // followed by m directed edges u v.
    size_t n, m, source, target;
    long long k;

    if (!(cin >> n >> m >> k >> source >> target)) {
        return 0;
    }

    if (n == 0 || k < 0 ||
        source >= n || target >= n) {
        cerr << "Invalid graph size, exponent, or vertex.\n";
        return 1;
    }

    Matrix A(n);

    for (size_t e = 0; e < m; ++e) {
        size_t u, v;

        if (!(cin >> u >> v) || u >= n || v >= n) {
            cerr << "Invalid edge.\n";
            return 1;
        }

        // Each edge contributes one possible transition.
        // Incrementing also supports parallel edges.
        A(u, v) = (A(u, v) + 1) % MOD;
    }

    cout << count_walks(
        A,
        static_cast<uint64>(k),
        source,
        target
    ) << '\n';

    return 0;
}
