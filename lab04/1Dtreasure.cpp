#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct State {
    int pos;
    ll total;
    vector<int> path;
};

void max_treasure_DFS_stack(const vector<int> &treasures_, vector<int> options_);

void solve() {
    // get the treasure map
    int n_; 
    if (!(cin >> n_)) return;
    vector<int> treasures_(n_);
    for (int &x : treasures_) cin >> x;
    
    // get the jump options, which will later be arbitrarily many
    vector<int> options_ = {1, 3};
    // int opt_; cin >> opt_;
    // vector<int> options_(opt_);
    // for (int &x : options_) cin >> x;

    max_treasure_DFS_stack(treasures_, options_);   
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

void max_treasure_DFS_stack(const vector<int> &treasures_, vector<int> options_) {
    // CRITICAL: For arbitrary jumps, the pruning logic requires the array to be sorted ascending.
    sort(options_.begin(), options_.end());

    vector<State> traversal_stack;
    traversal_stack.push_back({0, 0, {}});

    int n_ = (int)treasures_.size();

    ll best_total = LLONG_MIN;
    ll best_route = 0; 
    ll current_route = 0;

    while (!traversal_stack.empty()) {
        State current = traversal_stack.back();
        traversal_stack.pop_back();

        // OUT OF BOUND DETECTED (Goal State)
        if (current.pos >= n_) {
            cout << "Route #" << ++current_route << ": ";

            for (auto &x : current.path) {cout << x << "->";}
            cout << "F; value = "  << current.total << ".\n";

            // strictly greater (>) ensures we save the FIRST route to hit the max, mirroring Python's .index()
            if (current.total > best_total) {
                best_total = current.total;
                best_route = current_route;
            }
            continue;
        }

        // Compute the new total and new path exactly ONCE before branching, 
        // perfectly mirroring Python's `new_val = val + A[pos]` and `new_path = path + [pos]`
        ll new_total = current.total + treasures_[current.pos];
        vector<int> new_path = current.path;
        new_path.push_back(current.pos);

        // Explore all possible next jump options
        // Push the largest jumps FIRST so that the 
        // smallest jump ends up on top of the stack and is popped first.
        for (int i = (int)options_.size() - 1; i >= 0; i--) {
            int jump = options_[i];
            int next_pos = current.pos + jump;
            
            // If the PREVIOUS (smaller) jump already took us out of bounds, skip pushing.
            // This prevents generating duplicate "out-of-bound" endings from the same cell.
            if (i > 0 && current.pos + options_[i-1] >= n_) {
                continue;
            }

            traversal_stack.push_back({
                next_pos, 
                new_total, 
                new_path
            });
        }
    }
    
    cout << "Best: Route #" << best_route << " with value " << best_total << ".\n";
}