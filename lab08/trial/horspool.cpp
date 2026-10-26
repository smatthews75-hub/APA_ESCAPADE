#include <bits/stdc++.h>
using namespace std;

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
    getline(cin, text);
    getline(cin, pattern);
    size_t n = text.size(), m = pattern.size();

    if (n < m || m == 0) {
        cout << "no matches\n";
        return;
    }

    ShiftTable shift_table = create_table(pattern);

    size_t i = 0;

    while (i + m <= n) {
        size_t j = m;
        while (j > 0 && pattern[j - 1] == text[i + j - 1]) j--;
        // pattern[j - 1] != text[i + j - 1] mismatch never happened thus j == 0
        if (j == 0) { // match found
            cout << i << "\n";
            return; // only if first match needed, otherwise comment ts
        }
        // mismatch found, execute shift 
        i += shift_table[static_cast<unsigned char>(text[i + m - 1])];
    }
    cout << "no matches\n";
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