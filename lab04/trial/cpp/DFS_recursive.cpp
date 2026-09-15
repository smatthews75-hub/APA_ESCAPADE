#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Result {
    vector<int> visited_sequence;
    vector<int> jump_sequence;
    ll total = LLONG_MIN;
};

void update_best_res(
    Result &best, 
    const vector<int> &current_visited,
    const vector<int> &current_jumps,
    long long current_total) {
        if (current_total <= best.total) return;
        best.visited_sequence = current_visited;
        best.jump_sequence = current_jumps;
        best.total = current_total;
}

Result max_treasure_DFS_recursive(const vector<int> &treasures_, const vector<int> &options_);


void solve() {
    // get the treasure map
    int n_; cin >> n_;
    vector<int> treasures_(n_);
    for (int& x : treasures_) cin >> x;
    // get the jump options
    int opt_; cin >> opt_;
    vector<int> options_(opt_);
    for (int& x : options_) cin >> x;

    Result resDFSrecursive = max_treasure_DFS_recursive(treasures_, options_);

    auto print_res = [&treasures_](Result &res){
        for (auto &x: res.visited_sequence) {
            cout <<"["<<x<<"]:"<<treasures_[x]<<" ";
        }
        cout << "\n";
        for (auto &x: res.jump_sequence) {cout << x << " ";}
        cout << "\n";
        cout << "Max treasures : " << res.total;
        cout << "\n";
    };

    print_res(resDFSrecursive);
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


Result max_treasure_DFS_recursive(const vector<int> &treasures_, const vector<int> &options_) {
    // This one never had the copy problem: current_visited/current_jumps are a
    // single shared path mutated in place with push_back/pop_back backtracking,
    // so no state ever drags around a duplicate of the path. Left unchanged.
    Result best_res;
    vector<int> current_visited = {0}, current_jumps;

    function<void(int, long long)> dfs = 
    [&best_res, &dfs, &treasures_, &options_, &current_visited, &current_jumps]
    (int current_index, long long current_total) {
        bool has_next = false;
        // Explore all possible next jump options
        for (int jump : options_) {
            int next_index = current_index + jump;
            // Skip out of bound next jumps
            if (next_index  < 0 || next_index >= (int)treasures_.size()) {continue;}
            // Now its guaranteed to have next jumps
            has_next = true;
            // Set the current progress
            current_visited.push_back(next_index);
            current_jumps.push_back(jump);

            // DEPTH FIRST SEARCH TO REACH CHILD NODES
            dfs(next_index, current_total + treasures_[next_index]);

            // When it reaches here undo the progress to search for other child nodes
            current_visited.pop_back();
            current_jumps.pop_back();
        }
        // If it reaches a child node where it cant jump anywhere else
        if (!has_next) {
            update_best_res(
                best_res,
                current_visited,
                current_jumps,
                current_total
            );
        }
    };

    dfs(0, treasures_[0]);
    return best_res;
}