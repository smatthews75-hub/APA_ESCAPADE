#include <bits/stdc++.h>
using namespace std;

#define ll long long

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

    // cout << text << " " << pattern << endl;
    // size_t n = text.size(), m = pattern.size();
    int Q; cin >> Q; 

    ShiftTable shift_table = create_table(pattern);

    char query;
    for (int i = 0; i < Q; i++) {
        cin >> query;
        cout << shift_table[query] << "\n";
    }
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