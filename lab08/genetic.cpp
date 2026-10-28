#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using MapTable = array<ll, 256>;
static const ll MOD = 1000000007LL;

ll hash_string(string &str, ll len, ll D, MapTable &MAP) {
    ll value = 0;
    for (ll i = 0; i < len; i++) {
        unsigned char chr = MAP[static_cast<unsigned char>(str[i])];
        value = (value * D + chr) % MOD;
    }
    return value;
}

void solve() {
    int k; cin >> k;

    MapTable MAP;
    for (ll i = 0; i < k; i++) {
        char chr; cin >> chr;
        MAP[static_cast<unsigned char>(chr)] = i;
    }
    // vector<string> base(k);
    // for (string &b : base) cin >> b;

    string text, pattern;
    cin >> text >> pattern;
    const size_t n = text.size(), m = pattern.size();

    if (n < m || m == 0) {cout << "not found\n"; return;}

    const size_t window_count = n - m + 1;
    // high = D^(m-1) mod MOD. The "weight" of the LEFTMOST character in
    // a window, i.e. what we must subtract when that character leaves.
    ll high = 1;
    for (size_t i = 1; i < m; i++) { // [1, m) is m - 1 times
        high = (high * k) % MOD;
    }
    // vector<ll> codes; codes.reserve(n - m + 1);

    bool match_found = false;

    ll pattern_hash = hash_string(pattern, m, k, MAP);
    ll first_window_hash = hash_string(text, m, k, MAP);
    ll window_hash = first_window_hash;

    // codes.push_back(window_hash);

    for (size_t i = 0; i < window_count; i++) {
        // cheap check. Different hashes => strings are DEFINITELY different.
        // BUT equal hashes can be two different strings sharing one hash.
        if (window_hash == pattern_hash && text.compare(i, m, pattern) == 0) {
            cout << i << " ";

            match_found = true;
        }

        if (i + 1 < window_count) {
            ll out_chr = MAP[static_cast<unsigned char>(text[i])]; // leaves the window
            ll in_chr = MAP[static_cast<unsigned char>(text[i + m])]; // enters the window

            // remove the leftmost character's contribution
            window_hash -= (out_chr * high) % MOD;
            // The subtraction can go negative (C++ % keeps the sign of the left
            // operand, unlike Python). Add MOD to bring it back into [0, MOD).
            if (window_hash < 0) window_hash += MOD;

            // shift everything one place left (multiply by D) and append the new char
            window_hash = (window_hash * k + in_chr) % MOD;
            // codes.push_back(window_hash);
        }
    }
    if (!match_found) cout << "not found";
    cout << "\n";

    // for (ll& c : codes) cout << c << "\n";
    
    window_hash = first_window_hash;
    for (size_t i = 0; i < window_count; i++) {
        cout << window_hash << "\n";
        if (i + 1 < window_count) {
            ll out_chr = MAP[static_cast<unsigned char>(text[i])];
            ll in_chr = MAP[static_cast<unsigned char>(text[i + m])];

            window_hash -= (out_chr * high) % MOD;
            if (window_hash < 0) window_hash += MOD;
            window_hash = (window_hash * k + in_chr) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}