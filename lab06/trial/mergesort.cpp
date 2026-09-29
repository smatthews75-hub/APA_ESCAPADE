#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &A_, int l_, int m_, int r_) {
    vector<int> B_(r_ - l_ + 1);
    int i_ = l_;        // left half index
    int j_ = m_ + 1;    // right half index
    int k_ = 0;

    while (i_ <= m_ and j_ <= r_) {
        if (A_[i_] <= A_[j_]) B_[k_++] = A_[i_++];
        else B_[k_++] = A_[j_++];
    }
    while (i_ <= m_) B_[k_++] = A_[i_++];
    while (j_ <= r_) B_[k_++] = A_[j_++];
    k_ = 0;
    for (int t_ = l_; t_ <= r_; t_++) A_[t_] = B_[k_++];
}

void merge_sort(vector<int> &A_, int l_, int r_) {
    if (l_ >= r_) return;
    int m_ = (l_ + r_) / 2; // truncation for floor
    merge_sort(A_, l_, m_);
    merge_sort(A_, m_ + 1, r_);
    merge(A_, l_, m_, r_);
}

void solve() {
    int n_; cin >> n_;
    vector<int> A_(n_);
    for (int &x_ : A_) cin >> x_;
    vector<int> B_(A_);
    merge_sort(B_, 0, (int)B_.size() - 1);
    for (int &x_ : A_) cout << x_ << ' '; 
    cout << endl;
    for (int &x_ : B_) cout << x_ << ' ';
    cout << endl;
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