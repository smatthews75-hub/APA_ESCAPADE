#include <bits/stdc++.h>
using namespace std;
#define ll long long
/* TESTCASE INPUT
2 3
1 2 3
4 5 6
3 2
1 2 
3 4
5 6
*/
struct Matrix {
    int rows;
    int cols;
    vector<ll> m;
    Matrix(int row, int col) : rows(row), cols(col), m(rows * cols, 0) {}
    inline ll& operator()(int i, int j) {return m[i * cols + j];}
    inline const ll& operator()(int i, int j) const {return m[i * cols + j];}
    void print() {
        for (int i_ = 0; i_ < rows; i_++) {
            for (int j_ = 0; j_ < cols; j_++) {
                cout << (*this)(i_, j_) << ' ';
            }
            cout << '\n';
        }
    }
};

Matrix naive_multiplication(const Matrix &A_, const Matrix &B_) {
    // A.rows x (A.cols B.rows) x B.cols
    if (A_.cols != B_.rows) return Matrix(1, 1);
    Matrix C_(A_.rows, B_.cols);

    for (int i_ = 0; i_ < A_.rows; i_++) {
        for (int j_ = 0; j_ < B_.cols; j_++) {
            for (int k_ = 0; k_ < A_.cols; k_++) {
                C_(i_, j_) += A_(i_, k_) * B_(k_, j_);
            }
        }
    }
    return C_;
}

void solve() {
    int rowA, colA; cin >> rowA >> colA;
    Matrix A_(rowA, colA);
    for (ll &x_ : A_.m) cin >> x_;
    int rowB, colB; cin >> rowB >> colB;
    Matrix B_(rowB, colB);
    for (ll &x_ : B_.m) cin >> x_;
    Matrix C_naive = naive_multiplication(A_, B_);
    // A_.print();
    // B_.print();
    C_naive.print();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}