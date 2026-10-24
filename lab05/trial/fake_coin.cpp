#include <bits/stdc++.h>
using namespace std;

void findfakecoinDecision(size_t n, size_t idx) {
    // Using half open intervals [low, high) [0, n)
    size_t low = 0;
    size_t high = n; 
    // size_t low = 1;
    // size_t high = n + 1;

    while (high - low > 1) {
        size_t count = high - low;
        size_t mid = low + count / 2;

        // Even : [low, mid) vs [mid, high).
        if (count % 2 == 0) {
            if (idx < mid) {
                cout << "kiri\n";
                high = mid;
            } else {
                cout << "kanan\n";
                low = mid;
            }
        // Odd: [low, mid) vs [mid] vs (mid, high]
        } else {
            if (idx < mid) {
                cout << "kiri\n";
                high = mid;
            } else if (idx > mid) {
                cout << "kanan\n";
                low = mid + 1;
            // The excluded middle coin is the fake coin.
            } else break;
        }
    }
}

template<typename T, typename  Comparator = less<>>
size_t findfakecoinArray(vector<T> &array, Comparator comp = Comparator()) {
    // less<>    : fake coin is lighter
    // greater<> : fake coin is heavier
    // zero-based, half-open intervals [low, high).
    size_t low = 0;
    size_t high = array.size();
    
    using Sum = std::conditional_t<
        std::is_floating_point_v<T>,
        std::common_type_t<T, double>,
        std::common_type_t<T, long long>
    >;

    auto scaleSum = [&array](size_t begin, size_t end) -> Sum {
        return std::accumulate(array.begin() + begin, array.begin() + end, Sum());
    };

    while (high - low > 1) {
        size_t count = high - low;
        size_t mid = low + count / 2;

        // Even : [low, mid) vs [mid, high).
        if (count % 2 == 0) {
            Sum left = scaleSum(low, mid);
            Sum right = scaleSum(mid, high);
            if (comp(left, right)) {
                cout << "kiri\n";
                high = mid;
            } else {
                cout << "kanan\n";
                low = mid;
            }
        // Odd: [low, mid) vs [mid] vs (mid, high]
        } else {
            Sum left = scaleSum(low, mid);
            Sum right = scaleSum(mid + 1, high);
            if (comp(left, right)) {
                cout << "kiri\n";
                high = mid;
            } else if (comp(right, left)) {
                cout << "kanan\n";
                low = mid + 1;
            // The excluded middle coin is the fake coin.
            } else return mid;
        }
    }
    return low;
}

void solve1() {
    // n number of coins, idx where the fake coin is at
    size_t n, idx; cin >> n >> idx;
    // output decisions
    findfakecoinDecision(n, idx);
}

void solve2() {
    // expect an array of just 2 values of weights, 1 outlier, n - 1 uniform
    size_t n_; cin >> n_;
    vector<int> coins(n_);
    for (int &x: coins) cin >> x;
    // output decisions + index location of fake coin
    cout << findfakecoinArray(coins, less<>()) << '\n';
    // vector<float> coinsf(n_);
    // for (float &x: coinsf) cin >> x;
    // cout << findfakecoinArray(coins, [](const auto& a, const auto& b){
    //     return a - 1e-3 < b; // less
    //     return a > b - 1e-3; // greater
    // }) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve1();
    }
    return 0;
}