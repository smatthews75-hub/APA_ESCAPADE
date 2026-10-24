#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll binpow(ll base, ll exp, ll mod) {
    // Treats exponents as combination of power of 2s, as binary
    // ex: 13 = 0b1101, base^13 = base^8 + base^4 + base^1
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        // from LSB, base^exp only when LSB == 1, otherwise skip
        if (exp & 1) res = (res * base) % mod; // checks if LSB == 1
        // advance the base by powers of 2
        base = (base * base) % mod;
        exp >>= 1; // exp /= 2, replace the current LSB with the next
    }
    return res;
}

ll recursivebinpow(ll base, ll exp, ll mod) {
    if (exp == 0) return 1;
    ll half = recursivebinpow(base, exp / 2, mod);
    ll half_squared = (half * half) % mod; 
    if (exp % 2 == 0) return half_squared;
    // Modulo applied to base first to prevent long long overflow
    else return (half_squared * (base % mod)) % mod;
}

void solve() {
    // ll mod = 1000003
    ll a, k, mod; cin >> a >> k >> mod;
    cout << binpow(a, k, mod) << "\n";
    cout << recursivebinpow(a, k, mod) << "\n";
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