#include <bits/stdc++.h>
using namespace std;

#define ll long long

const long double EPS = 1e-9L;

vector<ll> scores;          // GPAs in hundredths (exact integers)
long double target_average; // R

long double best_error = numeric_limits<long double>::infinity();
vector<size_t> best_subset;

// Is `current` better than the best subset so far?
// 1) closer to R; 2) tie -> smaller size; 3) tie -> lexicographically first.
bool isBetter(const vector<size_t>& current, long double error) {
    if (best_subset.empty()) return true;
    if (error < best_error - EPS) return true;
    if (error > best_error + EPS) return false;
    if (current.size() != best_subset.size())
        return current.size() < best_subset.size();
    return current < best_subset;
}

void evaluateSubset(const vector<size_t>& current, ll sum) {
    if (current.empty()) return; // Empty subset has no average.

    long double average = (long double)sum / (100.0L * current.size());
    long double error = fabsl(average - target_average);

    if (isBetter(current, error)) {
        best_error = error;
        best_subset = current;
    }
}

void GenerateSubsets(size_t i, ll sum, vector<size_t>& current) {
    if (i == scores.size()) {
        evaluateSubset(current, sum);
        return;
    }
    // Exclude scores[i].
    GenerateSubsets(i + 1, sum, current);

    // Include scores[i].
    current.push_back(i);
    GenerateSubsets(i + 1, sum + scores[i], current);
    current.pop_back(); // backtrack
}

void solve() {
    size_t n;
    double r;
    cin >> n >> r;
    target_average = r;
    scores.resize(n);
    for (ll& x : scores) {
        double v; cin >> v;
        x = llround(v * 100.0);
    }

    best_error = numeric_limits<long double>::infinity();
    best_subset.clear();

    vector<size_t> current_subset;
    current_subset.reserve(n);
    GenerateSubsets(0, 0, current_subset);

    for (size_t i = 0; i < best_subset.size(); ++i) {
        if (i) cout << " ";
        cout << best_subset[i];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
