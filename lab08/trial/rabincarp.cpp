#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static const ll MOD = 1000000007;
static const ll D = 256; // 1 Byte char

/*
Best case: O(n + m). Example: text abcabcabc…, pattern xyz.
Hashing the pattern and first window costs O(m), and each roll is O(1). 
Equal hashes occur only at real matches, or not at all.
No hash ever matches, so nothing is verified. 

Unlike Horspool, it can never go below linear, because it reads every text character to update the hash.

Worst case: O(nm). Text aaaa…a with pattern aaaa…a
The O(m) verification step runs on many windows. There are two ways to get there:
Many genuine matches in all-matches mode. 
Text aaaa…a with pattern aaaa…a verifies every window, and each verification is a full O(m) compare. 
If you stop at the first match, this input is just O(n + m).

Many hash collisions (spurious hits). 
Different windows get the same hash, and compare runs until it finds a difference near the end. 
This needs a tiny modulus or an adversary who knows your base and modulus, for example D = 256 and MOD = 1e9+7. 
With a prime near 1e9 on ordinary input it essentially never happens. 
*/

// ---------------------------------------------------------------------------
// Rabin-Karp string matching (standard polynomial rolling hash)
//
// IDEA
//   Comparing the pattern with every window of the text character by character
//   costs O(n*m). Rabin-Karp instead turns every string of length m into ONE
//   number (its hash). Comparing two numbers is O(1). We only do the slow
//   character-by-character comparison when the two numbers are equal.
//
// THE HASH (treat a string as a number written in base D)
//   For a string s[0..m-1]:
//
//       hash(s) = ( s[0]*D^(m-1) + s[1]*D^(m-2) + ... + s[m-1]*D^0 )  mod MOD
//
//   This is exactly how "123" = 1*10^2 + 2*10^1 + 3*10^0 in base 10, except
//   our "digits" are character codes (0..255) so the base is D = 256, and we
//   take everything mod a large prime MOD so the number never overflows.
//
// THE ROLLING PART
//   Moving the window one step right (drop text[i], add text[i+m]) does not
//   require re-hashing m characters. Using the base-10 analogy again, going
//   from "123" to "234":
//       234 = (123 - 1*10^2) * 10 + 4
//   Same here:
//       new = ( (old - text[i] * D^(m-1)) * D + text[i+m] )  mod MOD
//   which is O(1) per step.
// ---------------------------------------------------------------------------

// Hash of the first `len` characters of `s`, using Horner's rule.
//
// Horner's rule evaluates  s[0]*D^(len-1) + ... + s[len-1]  without ever
// computing a power: start at 0, and for each character do
//       value = value * D + character
// Example (base 10, "123"):  0 -> 0*10+1 = 1 -> 1*10+2 = 12 -> 12*10+3 = 123.
ll hash_string(string &str, ll len) {
    ll value = 0;
    for (ll i = 0; i < len; i++) {
        unsigned char chr = static_cast<unsigned char>(str[i]);
        value = (value * D + chr) % MOD;
    }
    return value;
}

void solve() {
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);
    ll n = text.size(), m = pattern.size();

    if (n < m || m == 0) {cout << "no matches\n"; return;}

    // high = D^(m-1) mod MOD. The "weight" of the LEFTMOST character in
    // a window, i.e. what we must subtract when that character leaves.
    ll high = 1;
    for (ll i = 0; i < m - 1; i++) {
        high = (high * D) % MOD;
    }

    ll pattern_hash = hash_string(pattern, m);
    ll window_hash = hash_string(text, m);
    bool match_found = false;

    for (ll i = 0; i + m <= n; i++) {
        // cheap check. Different hashes => strings are DEFINITELY different.
        // BUT equal hashes can be two different strings sharing one hash.
        if (window_hash == pattern_hash && text.compare(i, m, pattern) == 0) {
            cout << i << "\n";
            for (int j = i; j < i + m; j++) {
                cout << text[j];
            }
            cout << "\n";
            match_found = true;
            // return; // comment if needed more than the first match
        }

        if (i + m < n) {
            ll out_chr = static_cast<unsigned char>(text[i]); // leaves the window
            ll in_chr = static_cast<unsigned char>(text[i + m]); // enters the window

            // remove the leftmost character's contribution
            window_hash = window_hash - (out_chr * high) % MOD;
            // The subtraction can go negative (C++ % keeps the sign of the left
            // operand, unlike Python). Add MOD to bring it back into [0, MOD).
            if (window_hash < 0) window_hash += MOD;

            // shift everything one place left (multiply by D) and append the new char
            window_hash = (window_hash * D + in_chr) % MOD;
        }
    }
    if (!match_found) {cout << "no matches\n"; return;}
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