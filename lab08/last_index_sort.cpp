#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct ScoreRange {
    string txt;
    float low = 0.0;
    float high = 100.1;
};

// Core search using half-open intervals [begin, end)
size_t binary_search(const std::vector<ScoreRange>& array, float target, size_t begin, size_t end) {

    size_t low = begin;
    size_t high = end;

    while (low < high) { 
        size_t mid = low + (high - low) / 2;
        // cout << low << " " << mid << " " << high << endl;

        ScoreRange curr_range = array[mid];
        // cout << curr_range.low << " : " << curr_range.high << " END1\n";

        if (curr_range.low <= target && target < curr_range.high) return mid;

        // [range.low, range.high) so [range.high range.high2)
        if (target >= curr_range.high) {
            low = mid + 1; 
        } else {
            high = mid; 
        }
        // cout << "END2\n";
    }
    return std::numeric_limits<size_t>::max(); 
}

size_t binary_search(const std::vector<ScoreRange>& array, float target) {
    // cout << "SIZE " << array.size() << endl;
    return binary_search(array, target, 0, array.size());
}

void solve() {
    int N, M, Q; cin >> N >> M >> Q;

    vector<float> scores(N);
    for (float &x: scores) cin >> x;
    
    vector<ScoreRange> score_ranges(M);
    float interval;
    int limit_M = M - 1;
    for (int b = 0; b < limit_M; b++) {
        cin >> interval;
        score_ranges[b].high = interval;
        score_ranges[b + 1].low = interval;
    }

    for (ScoreRange &x : score_ranges) cin >> x.txt;
    
    // for (ScoreRange &x : score_ranges) {
    //     cout << x.txt << ": " << x.low << " " << x.high << "\n";
    // }

    vector<int> bucket_ranks(M, 0);
    for (int n = 0; n < N; n++) bucket_ranks[binary_search(score_ranges, scores[n])]++;

    int query;
    for (int q = 0; q < Q; q++) {
        cin >> query;
        for (int b = M - 1; b >= 0; --b) {
            if (query <= bucket_ranks[b]) {
                cout << score_ranges[b].txt << '\n';
                break;
            }
            query -= bucket_ranks[b];
        }
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