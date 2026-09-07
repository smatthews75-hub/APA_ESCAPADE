// ============================================================================
// bignum_fast.hpp — Arbitrary-precision Integer + Decimal, PERFORMANCE variant
// ----------------------------------------------------------------------------
// Design goals: fastest arithmetic possible with pure std C++ (no Boost/GMP).
//   - Storage: base 1,000,000,000 limbs (vector<int32_t>), little-endian.
//     ~3.55 bits/decimal digit — dense, and each limb is already a printable
//     decimal chunk so I/O is trivial (no base conversion needed).
//   - Multiplication: Karatsuba, O(n^1.585) instead of schoolbook O(n^2).
//     Falls back to schoolbook below a small threshold (recursion overhead
//     isn't worth it for tiny operands).
//   - Division: long division with binary-search-per-digit. O(n^2 log(BASE))
//     but with a very small constant since it works in base-1e9 chunks.
//   - Trade-off vs bignum_compact.hpp: this uses ~4x more bytes per digit
//     internally during multiply (int64 accumulators) and more transient
//     memory during Karatsuba recursion, in exchange for speed.
//
// Usage: just like int/double —
//   BigInt a("123456789012345678901234567890"), b(999999937);
//   BigInt c = a * b + 1;
//   cin >> a; cout << a << "\n";
//   BigDecimal x("3.14159"), y("2.71828");
//   BigDecimal z = x * y;                       // exact
//   BigDecimal w = BigDecimal::divide(x, y, 20); // division to 20 dp
// ============================================================================
#pragma once
#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    static const int BASE = 1000000000;
    static const int BASE_DIGITS = 9;
    vector<int> a;   // little-endian, base-1e9 digits, no leading zero limb
    int sign = 1;    // +1 or -1 ; zero is always stored as sign=+1, a={}

    BigInt() {}
    BigInt(long long v) { *this = v; }
    BigInt(const string &s) { read(s); }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
        if (a.empty()) sign = 1;
    }
    bool isZero() const { return a.empty(); }

    BigInt& operator=(long long v) {
        sign = 1;
        if (v < 0) { sign = -1; v = -v; }
        a.clear();
        for (; v > 0; v /= BASE) a.push_back((int)(v % BASE));
        return *this;
    }

    void read(const string &s) {
        sign = 1; a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            pos++;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++)
                x = x * 10 + (s[j] - '0');
            a.push_back(x);
        }
        trim();
    }

    friend istream& operator>>(istream &in, BigInt &v) {
        string s; in >> s; v.read(s); return in;
    }
    friend ostream& operator<<(ostream &out, const BigInt &v) {
        if (v.sign == -1 && !v.isZero()) out << '-';
        out << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int)v.a.size() - 2; i >= 0; i--)
            out << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        return out;
    }
    string str() const { ostringstream ss; ss << *this; return ss.str(); }
    long long toLL() const {
        long long r = 0;
        for (int i = (int)a.size() - 1; i >= 0; i--) r = r * BASE + a[i];
        return r * sign;
    }

    // ---- magnitude helpers ----
    static vector<int> addVec(const vector<int>&x, const vector<int>&y) {
        vector<int> res; int carry = 0;
        for (size_t i = 0; i < max(x.size(), y.size()) || carry; i++) {
            int cur = carry + (i < x.size() ? x[i] : 0) + (i < y.size() ? y[i] : 0);
            res.push_back(cur % BASE);
            carry = cur / BASE;
        }
        return res;
    }
    static vector<int> subVec(const vector<int>&x, const vector<int>&y) { // x >= y
        vector<int> res = x; int borrow = 0;
        for (size_t i = 0; i < y.size() || borrow; i++) {
            res[i] -= borrow + (i < y.size() ? y[i] : 0);
            borrow = res[i] < 0;
            if (borrow) res[i] += BASE;
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }
    static int cmpAbs(const vector<int>&x, const vector<int>&y) {
        if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
        for (int i = (int)x.size() - 1; i >= 0; i--)
            if (x[i] != y[i]) return x[i] < y[i] ? -1 : 1;
        return 0;
    }
    static vector<int> mulSmall(const vector<int>&v, long long m) {
        vector<int> res(v.size()); long long carry = 0;
        for (size_t i = 0; i < v.size(); i++) {
            long long cur = (long long)v[i] * m + carry;
            res[i] = (int)(cur % BASE);
            carry = cur / BASE;
        }
        while (carry) { res.push_back((int)(carry % BASE)); carry /= BASE; }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

    // ---- + - unary- comparisons ----
    friend BigInt operator+(const BigInt &x, const BigInt &y) {
        BigInt res;
        if (x.sign == y.sign) { res.a = addVec(x.a, y.a); res.sign = x.sign; }
        else if (cmpAbs(x.a, y.a) >= 0) { res.a = subVec(x.a, y.a); res.sign = x.sign; }
        else { res.a = subVec(y.a, x.a); res.sign = y.sign; }
        res.trim(); return res;
    }
    friend BigInt operator-(const BigInt &x, const BigInt &y) {
        BigInt ny = y; if (!ny.isZero()) ny.sign = -ny.sign;
        return x + ny;
    }
    BigInt operator-() const { BigInt r = *this; if (!r.isZero()) r.sign = -r.sign; return r; }
    friend bool operator<(const BigInt &x, const BigInt &y) {
        if (x.sign != y.sign) return x.sign < y.sign;
        int c = cmpAbs(x.a, y.a);
        return x.sign == 1 ? c < 0 : c > 0;
    }
    friend bool operator==(const BigInt &x, const BigInt &y) { return x.sign == y.sign && x.a == y.a; }
    friend bool operator!=(const BigInt &x, const BigInt &y) { return !(x == y); }
    friend bool operator>(const BigInt &x, const BigInt &y) { return y < x; }
    friend bool operator<=(const BigInt &x, const BigInt &y) { return !(y < x); }
    friend bool operator>=(const BigInt &x, const BigInt &y) { return !(x < y); }

    // ---- Karatsuba multiplication ----
    static vector<long long> karatsuba(const vector<long long>&x, const vector<long long>&y) {
        int n = x.size();
        if (n <= 32) { // schoolbook base case
            vector<long long> res(2 * n, 0);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += x[i] * y[j];
            return res;
        }
        int k = n / 2;
        vector<long long> x1(x.begin(), x.begin() + k), x2(x.begin() + k, x.end());
        vector<long long> y1(y.begin(), y.begin() + k), y2(y.begin() + k, y.end());
        vector<long long> x1y1 = karatsuba(x1, y1);
        vector<long long> x2y2 = karatsuba(x2, y2);
        for (int i = 0; i < k; i++) x2[i] += x1[i];
        for (int i = 0; i < k; i++) y2[i] += y1[i];
        vector<long long> mid = karatsuba(x2, y2);
        for (size_t i = 0; i < x1y1.size(); i++) mid[i] -= x1y1[i];
        for (size_t i = 0; i < x2y2.size(); i++) mid[i] -= x2y2[i];
        vector<long long> res(2 * n, 0);
        for (size_t i = 0; i < x1y1.size(); i++) res[i] += x1y1[i];
        for (size_t i = 0; i < mid.size(); i++) res[i + k] += mid[i];
        for (size_t i = 0; i < x2y2.size(); i++) res[i + 2 * k] += x2y2[i];
        return res;
    }
    friend BigInt operator*(const BigInt &x, const BigInt &y) {
        BigInt res;
        if (x.isZero() || y.isZero()) return res;
        vector<long long> xa(x.a.begin(), x.a.end()), ya(y.a.begin(), y.a.end());
        size_t n = 1;
        while (n < max(xa.size(), ya.size())) n <<= 1;
        n <<= 1;
        xa.resize(n); ya.resize(n);
        vector<long long> c = karatsuba(xa, ya);
        res.a.resize(c.size());
        long long carry = 0;
        for (size_t i = 0; i < c.size(); i++) {
            long long cur = c[i] + carry;
            res.a[i] = (int)((cur % BASE + BASE) % BASE);
            carry = (cur - res.a[i]) / BASE;
        }
        while (carry) { res.a.push_back((int)(carry % BASE)); carry /= BASE; }
        res.sign = x.sign * y.sign;
        res.trim();
        return res;
    }
    friend BigInt operator*(const BigInt &x, long long m) {
        BigInt res;
        long long mm = m < 0 ? -m : m;
        res.a = mulSmall(x.a, mm);
        res.sign = x.sign * (m < 0 ? -1 : 1);
        res.trim();
        return res;
    }

    // ---- long division (binary-search digit) ----
    static pair<BigInt, BigInt> divmod(const BigInt &x, const BigInt &y) {
        BigInt q, cur;
        q.a.assign(x.a.size(), 0);
        vector<int> yMag = y.a;
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            cur.a.insert(cur.a.begin(), x.a[i]);
            cur.trim();
            int lo = 0, hi = BASE - 1, dig = 0;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                vector<int> t = mulSmall(yMag, mid);
                if (cmpAbs(t, cur.a) <= 0) { dig = mid; lo = mid + 1; } else hi = mid - 1;
            }
            q.a[i] = dig;
            cur.a = subVec(cur.a, mulSmall(yMag, dig));
        }
        q.trim(); cur.trim();
        return {q, cur};
    }
    friend BigInt operator/(const BigInt &x, const BigInt &y) {
        auto [q, r] = divmod(x, y);
        q.sign = q.isZero() ? 1 : x.sign * y.sign;
        return q;
    }
    friend BigInt operator%(const BigInt &x, const BigInt &y) {
        auto [q, r] = divmod(x, y);
        r.sign = r.isZero() ? 1 : x.sign;
        return r;
    }
    BigInt& operator+=(const BigInt &o) { return *this = *this + o; }
    BigInt& operator-=(const BigInt &o) { return *this = *this - o; }
    BigInt& operator*=(const BigInt &o) { return *this = *this * o; }
    BigInt& operator/=(const BigInt &o) { return *this = *this / o; }
    BigInt& operator%=(const BigInt &o) { return *this = *this % o; }
    BigInt& operator++() { return *this = *this + BigInt(1); }
    BigInt& operator--() { return *this = *this - BigInt(1); }
    BigInt operator++(int) { BigInt t = *this; ++(*this); return t; }
    BigInt operator--(int) { BigInt t = *this; --(*this); return t; }
};

// ----------------------------------------------------------------------------
// BigDecimal — unscaled BigInt + scale (digits after the decimal point),
// mirrors Java BigDecimal / Python Decimal semantics. Multiplication is exact;
// division requires an explicit target precision (like Python's Decimal
// context), since decimal division isn't always terminating (e.g. 1/3).
// ----------------------------------------------------------------------------
struct BigDecimal {
    BigInt unscaled;
    int scale = 0; // number of digits to the right of the decimal point

    BigDecimal() {}
    BigDecimal(const string &s) { read(s); }
    BigDecimal(long long v) { unscaled = v; scale = 0; }

    void read(const string &s) {
        scale = 0;
        int sign = 1, start = 0;
        if (!s.empty() && (s[0] == '-' || s[0] == '+')) { if (s[0] == '-') sign = -1; start = 1; }
        string digits; bool seenDot = false;
        for (int i = start; i < (int)s.size(); i++) {
            if (s[i] == '.') { seenDot = true; continue; }
            digits += s[i];
            if (seenDot) scale++;
        }
        unscaled.read(digits.empty() ? "0" : digits);
        if (sign == -1 && !unscaled.isZero()) unscaled.sign = -1;
    }
    friend istream& operator>>(istream &in, BigDecimal &v) { string s; in >> s; v.read(s); return in; }
    friend ostream& operator<<(ostream &out, const BigDecimal &v) {
        string s = v.unscaled.str();
        bool neg = false;
        if (!s.empty() && s[0] == '-') { neg = true; s = s.substr(1); }
        while ((int)s.size() <= v.scale) s = "0" + s;
        if (v.scale > 0) s.insert(s.size() - v.scale, ".");
        out << (neg ? "-" : "") << s;
        return out;
    }
    string str() const { ostringstream ss; ss << *this; return ss.str(); }

    static void align(BigDecimal &x, BigDecimal &y) {
        int s = max(x.scale, y.scale);
        if (x.scale < s) { x.unscaled = x.unscaled * (long long)pow(10, s - x.scale); x.scale = s; }
        if (y.scale < s) { y.unscaled = y.unscaled * (long long)pow(10, s - y.scale); y.scale = s; }
    }
    // NOTE: for scale differences > 18 the pow(10,..) shortcut overflows long long;
    // use scaleUp() below for very large scale gaps.
    static BigInt scaleUp(BigInt v, int n) { for (int i = 0; i < n; i++) v = v * BigInt(10); return v; }

    friend BigDecimal operator+(BigDecimal x, BigDecimal y) {
        int s = max(x.scale, y.scale);
        x.unscaled = scaleUp(x.unscaled, s - x.scale);
        y.unscaled = scaleUp(y.unscaled, s - y.scale);
        BigDecimal r; r.unscaled = x.unscaled + y.unscaled; r.scale = s; return r;
    }
    friend BigDecimal operator-(BigDecimal x, BigDecimal y) {
        int s = max(x.scale, y.scale);
        x.unscaled = scaleUp(x.unscaled, s - x.scale);
        y.unscaled = scaleUp(y.unscaled, s - y.scale);
        BigDecimal r; r.unscaled = x.unscaled - y.unscaled; r.scale = s; return r;
    }
    BigDecimal operator-() const { BigDecimal r = *this; r.unscaled = -r.unscaled; return r; }
    friend BigDecimal operator*(const BigDecimal &x, const BigDecimal &y) {
        BigDecimal r; r.unscaled = x.unscaled * y.unscaled; r.scale = x.scale + y.scale; return r;
    }
    // Division to a fixed number of decimal places (you choose the precision,
    // exactly like Python's decimal.Context(prec=...)).
    static BigDecimal divide(const BigDecimal &x, const BigDecimal &y, int resultScale) {
        int shift = resultScale + y.scale - x.scale;
        BigInt num = x.unscaled;
        if (shift > 0) num = scaleUp(num, shift);
        else for (int i = 0; i < -shift; i++) num = num / BigInt(10);
        BigDecimal r; r.unscaled = num / y.unscaled; r.scale = resultScale; return r;
    }
    friend bool operator<(BigDecimal x, BigDecimal y) {
        int s = max(x.scale, y.scale);
        x.unscaled = scaleUp(x.unscaled, s - x.scale);
        y.unscaled = scaleUp(y.unscaled, s - y.scale);
        return x.unscaled < y.unscaled;
    }
    friend bool operator==(BigDecimal x, BigDecimal y) {
        int s = max(x.scale, y.scale);
        x.unscaled = scaleUp(x.unscaled, s - x.scale);
        y.unscaled = scaleUp(y.unscaled, s - y.scale);
        return x.unscaled == y.unscaled;
    }
    friend bool operator!=(BigDecimal x, BigDecimal y) { return !(x == y); }
    friend bool operator>(BigDecimal x, BigDecimal y) { return y < x; }
    friend bool operator<=(BigDecimal x, BigDecimal y) { return !(y < x); }
    friend bool operator>=(BigDecimal x, BigDecimal y) { return !(x < y); }
    BigDecimal& operator+=(const BigDecimal &o) { return *this = *this + o; }
    BigDecimal& operator-=(const BigDecimal &o) { return *this = *this - o; }
    BigDecimal& operator*=(const BigDecimal &o) { return *this = *this * o; }
};
