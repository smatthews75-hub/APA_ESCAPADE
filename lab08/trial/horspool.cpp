#include <bits/stdc++.h>
using namespace std;

using ShiftTable = vector<size_t>;

/*
Best case: O(n/m). Example: text aaaaaaaaaaaa, pattern bbbb.
The window’s last character never appears in the pattern, 
so every shift is the full m and each window costs one comparison.
The last text character is a, which isn’t in the pattern. 
It mismatches immediately and shifts by 4, so about n/m comparisons in total.
If you stop at the first match, an occurrence at index 0 costs only O(m).

Worst case: O(nm). Example: text aaaa…a, pattern baaa…a.
Every window compares almost the whole pattern, then the shift is only 1.
The last character a has shift 1 (it occurs in the pattern’s second-to-last position). 
Each window matches m-1 characters from the right, then fails on the leading b. That is (n−m+1)·m comparisons.

If you print all matches, text aaaa…a with pattern aaaa…a is also O(nm), because every window is a full match.

Average case on typical text is roughly O(n/m), which is why it’s popular. 
The worst case comes from highly repetitive text and patterns, which do show up in practice, for example in DNA or in repeated log lines.
*/

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