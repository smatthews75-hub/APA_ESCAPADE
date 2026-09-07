#include <bits/stdc++.h>

using namespace std;

#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ll long long
#define pb push_back
#define all(v) (v).begin(), (v).end()

void solve() {
    string line;

    vector<double> x_points;
    vector<double> y_points;

    if (getline(cin, line)) {
        stringstream ss_x(line);
        double val;
        while (ss_x >> val) {
            x_points.pb(val);
        }
    }

    const size_t N = x_points.size();

    if (getline(cin, line)) {
        stringstream ss_y(line);
        double val;
        y_points.reserve(N);
        for (size_t i = 0; i < N; ++i) {
            ss_y >> val;
            y_points.pb(val);
        }
    }

    double min_dist2 = numeric_limits<double>::infinity();

    vector<pair<size_t, size_t>> min_pairs;

    for (size_t i = 0; i + 1 < N; ++i) {
        const double xi = x_points[i];
        const double yi = y_points[i];

        for (size_t j = i + 1; j < N; ++j) {
            const double dx = xi - x_points[j];
            const double dy = yi - y_points[j];

            const double dist2 = dx * dx + dy * dy;

            if (dist2 < min_dist2) {
                min_dist2 = dist2;

                min_pairs.clear();
                min_pairs.emplace_back(i, j);
            }
            else if (dist2 == min_dist2) {
                min_pairs.emplace_back(i, j);
            }
        }
    }

    const double min_dist = sqrt(min_dist2);

    cout << min_dist << '\n';

    for (const auto &[i, j] : min_pairs) {
        cout << i << ' ' << j << '\n';
    }
}

int main() {
    fast_io;

    uint8_t t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}