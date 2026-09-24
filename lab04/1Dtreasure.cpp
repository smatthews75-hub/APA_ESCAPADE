#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct State {
    int pos;
    ll total;
    vector<int> path;
};

void max_treasure_DFS_stack(const vector<int> &treasures_, const vector<int> &options_);

void solve() {
    // get the treasure map
    int n_; cin >> n_;
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

void max_treasure_DFS_stack(const vector<int> &treasures_, const vector<int> &options_) {

    vector<State> traversal_stack;
    traversal_stack.push_back({0, 0, {}});

    int n_ = (int)treasures_.size();

    ll best_total = LLONG_MIN;
    ll best_route = LLONG_MIN;
    ll current_route = 0;

    while (!traversal_stack.empty()) {
        auto current = traversal_stack.back();
        traversal_stack.pop_back();

        // OUT OF BOUND DETECTED
        if (current.pos >= n_) {
            cout << "Route #" << ++current_route << ": ";

            for (auto &x : current.path) {cout << x << "->";}
            cout << "F; value = "  << current.total << ".\n";

            if (current.total > best_total) {
                best_total = current.total;
                best_route = current_route;
            }
            continue;
        }
        // Explore all possible next jump options
        // Push the largest jumps FIRST so that the 
        // smallest jump ends up on top of the stack and is popped first.
        for (int i = (int)options_.size() - 1; i >= 0; i--) {
            int jump = options_[i];
            int next_pos = current.pos + jump;
            
            // If the a smaller jump would take it out of bounds, dont 
            // push any of the larger jumps. We only push a jump if the PREVIOUS 
            // (smaller) jump didn't already take us out of bounds.
            if (i > 0 && current.pos + options_[i-1] >= n_) {continue;}

            vector<int> next_path = current.path;
            next_path.push_back(current.pos);
            
            traversal_stack.push_back({
                next_pos, 
                current.total + treasures_[current.pos], 
                next_path
            });
        }
    }
    
    cout << "Best: Route #" << best_route << " with value " << best_total << ".\n";
}