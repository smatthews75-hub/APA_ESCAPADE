#include <bits/stdc++.h>
using namespace std;

#define ll long long

static void printresult(size_t iteration, size_t low, size_t mid, size_t high, int case_, string res) {
    cout << "Penimbangan #" << iteration << ": {kiri: ";
    cout << low << ".." << mid - 1 << ", kanan: ";
    switch (case_) {
        case 0:
            cout << mid << ".." << high - 1 << "}. Hasil: ";
            break;
        case 1:
            cout << mid << ".." << high - 2 << ", dipinggirkan: ";
            cout << high - 1 << "}. Hasil: ";
            break;
    }
    cout << res << "\n";
}

void findfakecoinDecision(size_t n, size_t idx) {
    // Using half open intervals [low, high) [0, n)
    size_t low = 0;
    size_t high = n;
    size_t iteration = 0;
    
    if (n == 1 && idx == 0) {
        high = 0; low = 0;
    }

    while (high - low > 0) {
        size_t count = high - low;
        size_t mid = low + count / 2;
        // Even : [low, mid) vs [mid, high).
        if (count % 2 == 0) {
            if (idx < mid) {
                printresult(++iteration, low, mid, high, 0, "Tangan kiri lebih ringan.");
                if (low == mid - 1) break;
                high = mid;
            }
            else if (mid <= idx) {
                printresult(++iteration, low, mid, high, 0, "Tangan kanan lebih ringan.");
                if (mid == high - 1) break;
                low = mid;
            }

        // Odd: [low, mid) vs [mid, high) vs [high]
        } else {
            if (idx == high - 1) {
                printresult(++iteration, low, mid, high, 1, "Kedua tangan seimbang.");
                break;
            }
            else if (idx < mid) {
                printresult(++iteration, low, mid, high, 1, "Tangan kiri lebih ringan.");
                if (low == mid - 1) break;
                high = mid;
            }
            else if (mid <= idx) {
                printresult(++iteration, low, mid, high, 1, "Tangan kanan lebih ringan.");
                if (mid == high - 2) break;
                low = mid;
                high--;
            }
        }
    }
    cout << "Ketemu! Koin palsu adalah koin " << idx << ". Total penimbangan dilakukan: " << iteration << ".\n";
}


void solve() {
    size_t N, K; cin >> N >> K;
    findfakecoinDecision(N, K);
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