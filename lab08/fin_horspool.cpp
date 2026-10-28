#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using ShiftTable = vector<size_t>;

ShiftTable create_table(const string &pattern, size_t alphabet_size = 256) {
    size_t m = pattern.size();
    ShiftTable table(256, m);
    if (m == 0) return table;

    size_t distinct = 0;
    for (size_t i = m - 1; i-- > 0;) { // i = m-2 down to 0
        unsigned char c = static_cast<unsigned char>(pattern[i]);
        // unsigned char chr = toupper(static_cast<unsigned char>(pattern[i]));
        if (table[c] == m) {// first (= rightmost) occurrence
            // set shifts m - 1 pattern indeces - i char indeces
            table[c] = m - 1 - i;
            if (++distinct == alphabet_size) break;
        }
    }
    return table;
}

void solve() {
    string text, pattern;
    cin >> text >> pattern;
    // getline(cin, text);
    // getline(cin, pattern);
    size_t n = text.size(), m = pattern.size();
    // cout << n << " " << m << "\n";
    if (n < m || m == 0) {
        cout << "not found\n";
        return;
    }

    ShiftTable shift_table = create_table(pattern);

    size_t i = 0;
    bool match_found = false;

    ll Horspool_shift_count = 0;
    while (i + m <= n) {
        size_t j = m;
        while (j > 0 && pattern[j - 1] == text[i + j - 1]) j--;

        // pattern[j - 1] != text[i + j - 1] mismatch never happened thus j == 0
        if (j == 0) { // match found
            cout << i << " ";
            match_found = true;
            // return; // only if first match needed, otherwise comment ts
        }
        // mismatch found, execute shift 
        i += shift_table[static_cast<unsigned char>(text[i + m - 1])];
        Horspool_shift_count ++;
    }
    if (!match_found) cout << "not found";
    cout << "\n";
    
    int naive_shift = (n - m + 1);
    float improvement = (static_cast<float>(naive_shift - Horspool_shift_count) / naive_shift) * 100.0;
    std::cout << std::fixed << std::setprecision(2);
    cout << improvement << "%\n";
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