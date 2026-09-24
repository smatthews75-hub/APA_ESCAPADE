#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Result {
    string print_out = "";
    ll total = LLONG_MIN;
    ll route = LLONG_MIN;
};

// struct Node {
//     int idx;      // treasure index this node represents
//     ll total;     // cumulative treasure total up to and including this node
//     int parent;   // index into the same pool, -1 for the root
// };

// Same "strictly greater, ties keep whichever leaf was found first" semantics
// as update_best_res, just tracking a pool index + total instead of copying
// whole path vectors around on every candidate.
// void update_best_leaf(ll &best_route, int &best_leaf, ll &best_total, int candidate_leaf, ll candidate_total, ll candidate_route) {
//     if (candidate_total <= best_total) return;
//     best_leaf = candidate_leaf;
//     best_total = candidate_total;
//     best_route = candidate_route;
// }

// Reconstructs a Result from a leaf's position in the node pool.
// O(depth), and it's only ever called once per search, on the best leaf found.
// Result build_result(const vector<Node> &pool, int leaf_node) {
//     Result res;
//     if (leaf_node == -1) return res; // no leaf found (shouldn't happen: jumps are
//                                       // positive-only, so every path is finite)
//     res.total = pool[leaf_node].total;
//     int cur = leaf_node;
//     while (cur != -1) {
//         res.visited_sequence.push_back(pool[cur].idx);
//         cur = pool[cur].parent;e
//     }
//     reverse(res.visited_sequence.begin(), res.visited_sequence.end());
//     return res;
// }

void max_treasure_DFS_stack(const vector<int> &treasures_, const vector<int> &options_);


void solve() {
    // get the treasure map
    int n_; cin >> n_;
    vector<int> treasures_(n_);
    for (int& x : treasures_) cin >> x;
    // get the jump options
    vector<int> options_ = {1, 2};

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
    // Node pool holds every step ever created during the search. Growing it is
    // just a push_back of a small fixed-size struct - nothing here ever copies
    // a path, unlike the old State{visited_sequence, jump_sequence} copies.
    // vector<Node> pool;
    // pool.push_back({0, treasures_[0], -1});

    stack<pair<int, int>> traversal_stack; // stack of pool indices, not full states
    traversal_stack.push({0, treasures_[0]});

    int n_ = (int)treasures_.size();

    string pending_printf = "";
    string pending_print = "";

    Result BEST_RES;
    ll route = 0;
    while (!traversal_stack.empty()) {
        auto current_pair = traversal_stack.top();
        int current_node = current_pair.first;
        int current_total = current_pair.second;
        traversal_stack.pop();
        bool has_next = false;
        if (current_node == n_) {
            string PRINT = "Route #" + to_string(++route) + ": ";

            vector<int> visited;
            auto destructible = traversal_stack;
            while (!destructible.empty()) {
                auto pair_ = destructible.top();
                destructible.pop();
                visited.push_back(pair_.first);
            }
            reverse(visited.begin(), visited.end());
            for (auto &x : visited) {
                PRINT += to_string(x) + "->";
            }
            PRINT += "F; value = " + to_string(current_total) + ".\n";
            cout << PRINT;
            if (current_total <= BEST_RES.total) {continue;}
            BEST_RES.total = current_total;
            BEST_RES.print_out = PRINT;
            continue;
        }

        // Explore all possible next jump options
        for (int jump : options_) {
            int next_index = current_total + jump;
            // Skip out of bound next jumps
            if (next_index >= n_) {
                traversal_stack.push({
                    n_,
                    current_total
                });
                continue;
            }
            // Now its guaranteed to have next jumps
            has_next = true;
            // Record the next step as a child of "current" - O(1), no path copy
            traversal_stack.push({
                next_index,
                current_total + treasures_[next_index]
            });
        }
        // If it reaches a child node where it cant jump anywhere else
        if (!has_next) {
            string PRINT = "Route #" + to_string(++route) + ": ";

            vector<int> visited;
            auto destructible = traversal_stack;
            while (!destructible.empty()) {
                auto pair_ = destructible.top();
                destructible.pop();
                visited.push_back(pair_.first);
            }
            reverse(visited.begin(), visited.end());
            for (auto &x : visited) {
                PRINT += to_string(x) + "->";
            }
            PRINT += "F; value = " + to_string(current_total) + ".\n";
            cout << PRINT;
            if (current_total <= BEST_RES.total) {continue;}
            BEST_RES.total = current_total;
            BEST_RES.print_out = PRINT;
            BEST_RES.route = route;
        }
    }
    
    cout << "Best: Route #" << BEST_RES.route << " with value " << BEST_RES.total;
}