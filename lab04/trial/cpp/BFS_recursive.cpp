#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct Result {
    vector<int> visited_sequence;
    vector<int> jump_sequence;
    ll total = LLONG_MIN;
};

struct Node {
    int idx;      // treasure index this node represents
    ll total;     // cumulative treasure total up to and including this node
    int parent;   // index into the same pool, -1 for the root
    int jump;     // jump used to get here from parent (unused when parent == -1)
};

// Same "strictly greater, ties keep whichever leaf was found first" semantics
// as update_best_res, just tracking a pool index + total instead of copying
// whole path vectors around on every candidate.
void update_best_leaf(int &best_leaf, ll &best_total, int candidate_leaf, ll candidate_total) {
    if (candidate_total <= best_total) return;
    best_leaf = candidate_leaf;
    best_total = candidate_total;
}

// Reconstructs a Result from a leaf's position in the node pool.
// O(depth), and it's only ever called once per search, on the best leaf found.
Result build_result(const vector<Node> &pool, int leaf_node) {
    Result res;
    if (leaf_node == -1) return res; // no leaf found (shouldn't happen: jumps are
                                      // positive-only, so every path is finite)
    res.total = pool[leaf_node].total;
    int cur = leaf_node;
    while (cur != -1) {
        res.visited_sequence.push_back(pool[cur].idx);
        if (pool[cur].parent != -1) {
            res.jump_sequence.push_back(pool[cur].jump);
        }
        cur = pool[cur].parent;
    }
    reverse(res.visited_sequence.begin(), res.visited_sequence.end());
    reverse(res.jump_sequence.begin(), res.jump_sequence.end());
    return res;
}

Result max_treasure_BFS_recursive(const vector<int> &treasures_, const vector<int> &options_);


void solve() {
    // get the treasure map
    int n_; cin >> n_;
    vector<int> treasures_(n_);
    for (int& x : treasures_) cin >> x;
    // get the jump options
    int opt_; cin >> opt_;
    vector<int> options_(opt_);
    for (int& x : options_) cin >> x;

    Result resDFSstack = max_treasure_BFS_recursive(treasures_, options_);

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

    print_res(resDFSstack);    
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


Result max_treasure_BFS_recursive(const vector<int> &treasures_, const vector<int> &options_) {
    // Same node-pool fix; the recursion still does nothing but drive the queue
    // processing one pop at a time, exactly like the original.
    vector<Node> pool;
    pool.push_back({0, treasures_[0], -1, 0});

    int best_leaf = -1;
    ll best_total = LLONG_MIN;

    queue<int> traversal_queue; // queue of pool indices, not full states
    traversal_queue.push(0);

    function<void()> BFS_process_queue =
    [&best_leaf, &best_total, &BFS_process_queue, &treasures_, &options_, &traversal_queue, &pool]
    (){
        // Base case to stop recursion
        if (traversal_queue.empty()) {return;}
        // BASICALLY QUEUE PROCESSING LITERALLY ONE TO ONE
        int current = traversal_queue.front();
        traversal_queue.pop();
        bool has_next = false;
        // Explore all possible next jump options
        for (int jump : options_) {
            int next_index = pool[current].idx + jump;
            // Skip out of bound next jumps
            if (next_index  < 0 || next_index >= (int)treasures_.size()) {continue;}
            // Now its guaranteed to have next jumps
            has_next = true;
            pool.push_back({
                next_index, 
                pool[current].total + treasures_[next_index], 
                current, 
                jump
            });
            traversal_queue.push((int)pool.size() - 1);
        }
        // If it reaches a child node where it cant jump anywhere else
        if (!has_next) {
            update_best_leaf(
                best_leaf,
                best_total,
                current,
                pool[current].total
            );
        }
        // Continue the recursion to continue processing the queue
        BFS_process_queue();
    };

    BFS_process_queue();
    return build_result(pool, best_leaf);
}