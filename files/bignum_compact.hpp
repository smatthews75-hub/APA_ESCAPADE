// ============================================================================
// bignum_compact.hpp — Arbitrary-precision Integer + Decimal, MEMORY variant
// ----------------------------------------------------------------------------
// Design goals: smallest possible memory footprint per stored number.
//   - Storage: base-256 limbs (vector<uint8_t>), little-endian — i.e. the
//     number's actual binary representation, one byte per limb.
//       * This hits the theoretical density ceiling for a byte-addressable
//         type: every one of the 8 bits in each byte is "real" information
//         (no base-1e9-style waste, no packed-BCD waste). A 1000-digit
//         number needs ceil(1000*log2(10)/8) ≈ 416 bytes here, vs ~444 bytes
//         for base-1e9 int32 limbs.
//       * It also means a *small* number costs almost nothing: BigInt(5) is
//         1 byte, not a whole 4-byte int32 limb like the fast variant.
//   - Multiplication/division: plain schoolbook, O(n^2), no Karatsuba —
//     Karatsuba's recursive temp arrays would themselves cost memory, which
//     defeats the point of this variant. You get a smaller footprint and
//     smaller peak memory during ops, at the cost of raw speed.
//   - Trade-off vs bignum_fast.hpp: ~4x more limbs to loop over for the same
//     number (8 bits/limb vs ~30 bits/limb), so multiply/divide are slower.
//     Printing/reading costs a bit more too (binary<->decimal conversion),
//     but that's a one-off O(n^2/64) cost, not a storage cost.
//
// Usage is identical to the fast variant — same operators, same interface:
//   BigInt a("123456789012345678901234567890"), b(999999937);
//   BigInt c = a * b + 1;
//   BigDecimal x("3.14159"), y("2.71828");
//   BigDecimal w = BigDecimal::divide(x, y, 20);
// ============================================================================
#pragma once
#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    vector<uint8_t> a; // little-endian, base-256 (raw binary) magnitude
    int sign = 1;       // +1 or -1 ; zero is always stored as sign=+1, a={}

    BigInt() {}
    BigInt(long long v) { *this = v; }
    BigInt(const string &s) { read(s); }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
        if (a.empty()) sign = 1;
    }
    bool isZero() const { return a.empty(); }

    BigInt& operator=(long long v) {
        sign = v < 0 ? -1 : 1;
        unsigned long long uv = v < 0 ? (unsigned long long)(-(v + 1)) + 1 : (unsigned long long)v;
        a.clear();
        while (uv) { a.push_back((uint8_t)(uv & 0xFF)); uv >>= 8; }
        return *this;
    }

    // ---- small-value helpers on raw magnitude (non-mutating unless noted) ----
    // NOTE: these use uint64_t accumulators, not uint32_t. m/d/x here can be
    // as large as 1e9 (used by str()/read() to move 9 decimal digits at a
    // time), and since each limb is only a byte, intermediate products like
    // v[i]*m or rem*256 need up to ~40 bits — uint32_t silently overflows
    // there and corrupts every digit above the low ones.
    static void mulSmallInPlace(vector<uint8_t> &v, uint32_t m) {
        uint64_t carry = 0;
        for (size_t i = 0; i < v.size(); i++) {
            uint64_t cur = (uint64_t)v[i] * m + carry;
            v[i] = (uint8_t)(cur & 0xFF);
            carry = cur >> 8;
        }
        while (carry) { v.push_back((uint8_t)(carry & 0xFF)); carry >>= 8; }
    }
    static void addSmallInPlace(vector<uint8_t> &v, uint32_t x) {
        size_t i = 0;
        uint64_t carry = x;
        while (carry) {
            if (i == v.size()) v.push_back(0);
            uint64_t cur = v[i] + (carry & 0xFF);
            v[i] = (uint8_t)(cur & 0xFF);
            carry = (carry >> 8) + (cur >> 8);
            i++;
        }
    }
    static uint32_t divSmallInPlace(vector<uint8_t> &v, uint32_t d) { // returns remainder
        uint64_t rem = 0;
        for (int i = (int)v.size() - 1; i >= 0; i--) {
            uint64_t cur = (rem << 8) | v[i];
            v[i] = (uint8_t)(cur / d);
            rem = cur % d;
        }
        while (!v.empty() && v.back() == 0) v.pop_back();
        return (uint32_t)rem;
    }
    static vector<uint8_t> mulSmall(const vector<uint8_t> &v, uint32_t m) {
        vector<uint8_t> r = v; mulSmallInPlace(r, m);
        // mulSmallInPlace only ever *extends* on carry, so an m==0 (or any
        // multiply that produces a zero result) leaves stale trailing zero
        // limbs from the original copy — trim them or size-based magnitude
        // comparisons (cmpAbs) elsewhere will be wrong.
        while (!r.empty() && r.back() == 0) r.pop_back();
        return r;
    }

    void read(const string &s) {
        sign = 1; a.clear();
        int pos = 0;
        if (!s.empty() && (s[0] == '-' || s[0] == '+')) { if (s[0] == '-') sign = -1; pos = 1; }
        for (int i = pos; i < (int)s.size(); i++) {
            mulSmallInPlace(a, 10);
            addSmallInPlace(a, (uint32_t)(s[i] - '0'));
        }
        trim();
    }
    friend istream& operator>>(istream &in, BigInt &v) { string s; in >> s; v.read(s); return in; }

    string str() const {
        if (a.empty()) return "0";
        vector<uint8_t> t = a;
        string digits;
        while (!t.empty()) {
            uint32_t rem = divSmallInPlace(t, 1000000000u);
            char buf[10];
            if (t.empty()) snprintf(buf, sizeof(buf), "%u", rem);
            else snprintf(buf, sizeof(buf), "%09u", rem);
            digits = string(buf) + digits;
        }
        return (sign < 0 ? "-" : "") + digits;
    }
    friend ostream& operator<<(ostream &out, const BigInt &v) { out << v.str(); return out; }

    // ---- magnitude compare / add / sub ----
    static int cmpAbs(const vector<uint8_t>&x, const vector<uint8_t>&y) {
        if (x.size() != y.size()) return x.size() < y.size() ? -1 : 1;
        for (int i = (int)x.size() - 1; i >= 0; i--)
            if (x[i] != y[i]) return x[i] < y[i] ? -1 : 1;
        return 0;
    }
    static vector<uint8_t> addVec(const vector<uint8_t>&x, const vector<uint8_t>&y) {
        vector<uint8_t> res; int carry = 0;
        for (size_t i = 0; i < max(x.size(), y.size()) || carry; i++) {
            int cur = carry + (i < x.size() ? x[i] : 0) + (i < y.size() ? y[i] : 0);
            res.push_back((uint8_t)(cur & 0xFF));
            carry = cur >> 8;
        }
        return res;
    }
    static vector<uint8_t> subVec(const vector<uint8_t>&x, const vector<uint8_t>&y) { // x >= y
        vector<uint8_t> res = x; int borrow = 0;
        for (size_t i = 0; i < y.size() || borrow; i++) {
            int cur = res[i] - borrow - (i < y.size() ? y[i] : 0);
            borrow = cur < 0;
            if (borrow) cur += 256;
            res[i] = (uint8_t)cur;
        }
        while (!res.empty() && res.back() == 0) res.pop_back();
        return res;
    }

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

    // ---- schoolbook multiply (kept simple on purpose — no extra temp arrays) ----
    friend BigInt operator*(const BigInt &x, const BigInt &y) {
        BigInt res;
        if (x.isZero() || y.isZero()) return res;
        vector<uint8_t> tmp(x.a.size() + y.a.size(), 0);
        for (size_t i = 0; i < x.a.size(); i++) {
            if (x.a[i] == 0) continue;
            uint32_t carry = 0;
            for (size_t j = 0; j < y.a.size(); j++) {
                uint32_t cur = tmp[i + j] + (uint32_t)x.a[i] * y.a[j] + carry;
                tmp[i + j] = (uint8_t)(cur & 0xFF);
                carry = cur >> 8;
            }
            size_t k = i + y.a.size();
            while (carry) {
                uint32_t cur = tmp[k] + carry;
                tmp[k] = (uint8_t)(cur & 0xFF);
                carry = cur >> 8;
                k++;
            }
        }
        res.a = move(tmp);
        res.sign = x.sign * y.sign;
        res.trim();
        return res;
    }
    friend BigInt operator*(const BigInt &x, long long m) {
        BigInt res;
        long long mm = m < 0 ? -m : m;
        res.a = x.a; mulSmallInPlace(res.a, (uint32_t)mm);
        res.sign = x.sign * (m < 0 ? -1 : 1);
        res.trim();
        return res;
    }

    // ---- long division (binary-search per byte, base is only 256 so it's cheap) ----
    static pair<BigInt, BigInt> divmod(const BigInt &x, const BigInt &y) {
        BigInt q, cur;
        q.a.assign(x.a.size(), 0);
        const vector<uint8_t> &yMag = y.a;
        for (int i = (int)x.a.size() - 1; i >= 0; i--) {
            cur.a.insert(cur.a.begin(), x.a[i]);
            cur.trim();
            int lo = 0, hi = 255, dig = 0;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                vector<uint8_t> t = mulSmall(yMag, mid);
                if (cmpAbs(t, cur.a) <= 0) { dig = mid; lo = mid + 1; } else hi = mid - 1;
            }
            q.a[i] = (uint8_t)dig;
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
// BigDecimal — same unscaled-value + scale design as the fast variant, just
// built on the compact BigInt above. Interface is identical on purpose so you
// can swap headers without touching the rest of your solution.
// ----------------------------------------------------------------------------
struct BigDecimal {
    BigInt unscaled;
    int scale = 0;

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
