#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Result {
    ll res;
    ll k;
};

Result binpow(ll base, ll exp, ll mod) {
    if (exp == 0) return {1 % mod, 0};
    // Treats exponents as combination of power of 2s, as binary
    // ex: 13 = 0b1101, base^13 = base^8 + base^4 + base^1
    ll res = 1 % mod;
    ll k = 0;
    base %= mod;
    bool is_first = true;
    while (true) {
        // from LSB, base^exp only when LSB == 1, otherwise skip
        if (exp & 1) {
            if (is_first) {
                res = base;
                is_first = false;
            } else {
                res = (res * base) % mod;
                k++; // one extra mult for odd exponents
            }
        } // checks if LSB == 1
        exp >>= 1; // exp /= 2, replace the current LSB with the next
        if (exp == 0) break; // skip the useless final squaring
        base = (base * base) % mod; // advance the base by powers of 2
        k++; // squaring
    }
    return {res, k};
}

ll recursivebinpow(ll base, ll exp, ll mod, ll &k) {
    if (exp == 0) return 1 % mod;
    if (exp == 1) return base;
    ll half = recursivebinpow(base, exp / 2, mod, k);
    ll half_squared = (half * half) % mod;
    k++; // squaring
    if (exp & 1) { // bitwise AND checks if LSB == 1, if exp is odd
        k++; // one extra mult for odd exponents
        // modulo applied to base is_first to prevent long long overflow
        return (half_squared * (base % mod)) % mod;
    } else return half_squared; // if exp is even
}
Result recursivePow(ll base, ll exp, ll mod){
    ll k = 0;
    base %= mod;
    ll res = recursivebinpow(base, exp, mod, k);
    return {res, k};
}

void solve() {
    ll A, B, MOD; cin >> A >> B >> MOD;
    // Result PLEASE = binpow(A, B, MOD);
    // cout << PLEASE.res << " " << PLEASE.k << "\n";
    ll k = 0;
    ll res = recursivebinpow(A, B, MOD, k);
    cout << res << " " << k << "\n";
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