#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<double> scores;
double target_average;

double best_error = numeric_limits<double>::infinity();
double best_average = 0.0;
double best_sum = 0.0;

vector<size_t> best_subset;

void evaluateSubset(const vector<size_t>& current, double sum) {
    if (current.empty()) return; // Empty subset has no average.

    double average = sum / current.size();
    double error = abs(average - target_average);

    // Keep only the best candidate found so far.
    if (error < best_error) {
        best_error = error;
        best_average = average;
        best_sum = sum;
        best_subset = current;
    }
}


void PrintSubset(const vector<size_t>& subset) {
    cout << "{";
    bool first = true;
    for (auto it = subset.begin(); it != subset.end(); it++) {
        if (!first) cout << ", ";
        cout << scores[*it];
        first = false;
    }
    cout << "}\n";
}
void GenerateSubsets(size_t i, double sum, vector<size_t>& current) {
    // Every element has been considered.
    if (i == scores.size()) {
        evaluateSubset(current, sum);
        PrintSubset(current);
        return;
    }

    // Case 1: Exclude scores[i].
    GenerateSubsets(i + 1, sum, current);

    // Case 2: Include scores[i].
    current.push_back(i);

    GenerateSubsets(i + 1, sum + scores[i], current);

    // Backtrack before exploring other subsets.
    current.pop_back();
}


void reversedPrintSubset(const vector<size_t>& subset) {
    cout << "{";
    bool first = true;
    // Reverse the indices because recursion selects higher indices first.
    for (auto it = subset.rbegin(); it != subset.rend(); it++) {
        if (!first) cout << ", ";
        cout << scores[*it];
        first = false;
    }
    cout << "}\n";
    // cout << "} ";
}
void reversedGenerateSubsets(size_t remaining, double sum, vector<size_t>& current) {
    // All elements have been considered.
    if (remaining == 0) {
        evaluateSubset(current, sum);
        reversedPrintSubset(current);
        return;
    }
    // Consider the highest remaining index first.
    size_t idx = remaining - 1;
    // if (remaining == current.size()) cout << "\n";

    // Case 1: Exclude scores[idx].
    reversedGenerateSubsets(idx, sum, current);

    // Case 2: Include scores[idx].
    current.push_back(idx);
    reversedGenerateSubsets(idx, sum + scores[idx], current);
    
    // Backtrack before exploring other subsets.
    current.pop_back();
}


void solve() {
    size_t n;
    cin >> n >> target_average;
    scores.resize(n);
    for (double& x : scores) cin >> x;

    // Reset the best candidate.
    best_error = numeric_limits<double>::infinity();
    best_average = 0.0;
    best_sum = 0.0;
    best_subset.clear();

    vector<size_t> current_subset;
    current_subset.reserve(n);
    best_subset.reserve(n);

    GenerateSubsets(0, 0.0, current_subset);
    cout << "=========================================================\n";
    reversedGenerateSubsets(n, 0.0, current_subset);

    if (best_subset.empty()) {
        cout << "No non-empty subset exists.\n";
        return;
    }

    cout << fixed << setprecision(3);

    cout << "Best subset: {";

    for (size_t i = 0; i < best_subset.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << scores[best_subset[i]];
    }

    cout << "}\n";
    cout << "Subset size: " << best_subset.size() << '\n';
    cout << "Sum: " << best_sum << '\n';
    cout << "Average: " << best_average << '\n';

    // More precision here makes small differences easier to inspect.
    cout << setprecision(9);
    cout << "Absolute error: " << best_error << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}