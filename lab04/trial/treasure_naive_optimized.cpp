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

// A single visited step in the search tree.
// The original bug: every in-flight state carried its OWN full copy of
// visited_sequence/jump_sequence, so every child creation cost O(depth) and
// every state sitting in the stack/queue held a redundant duplicate of the
// whole path so far. Fix: each step only remembers its own idx/total and
// WHERE it came from (parent). The full path for any node can always be
// recovered later by walking parent links back to the root, so that O(depth)
// cost is only ever paid once - for the single winning leaf - instead of on
// every single node created during the traversal.
struct Node {
    int idx;      // treasure index this node represents
    ll total;     // cumulative treasure total up to and including this node
    int parent;   // index into the same pool, -1 for the root
    int jump;     // jump used to get here from parent (unused when parent == -1)
};

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

// Same "strictly greater, ties keep whichever leaf was found first" semantics
// as update_best_res, just tracking a pool index + total instead of copying
// whole path vectors around on every candidate.
void update_best_leaf(int &best_leaf, ll &best_total, int candidate_leaf, ll candidate_total) {
    if (candidate_total <= best_total) return;
    best_leaf = candidate_leaf;
    best_total = candidate_total;
}

Result max_treasure_DFS_stack(const vector<int> &treasures_, const vector<int> &options_);
Result max_treasure_DFS_recursive(const vector<int> &treasures_, const vector<int> &options_);
Result max_treasure_BFS_queue(const vector<int> &treasures_, const vector<int> &options_);
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

    Result resBFSqueue = max_treasure_BFS_queue(treasures_, options_); 
    Result resBFSrecursive = max_treasure_BFS_recursive(treasures_, options_);
    Result resDFSstack = max_treasure_DFS_stack(treasures_, options_);
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
    print_res(resBFSqueue);
    cout << "========================================================\n";
    print_res(resBFSrecursive);
    cout << "========================================================\n";
    print_res(resDFSstack);
    cout << "========================================================\n";
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


Result max_treasure_DFS_stack(const vector<int> &treasures_, const vector<int> &options_) {
    // Node pool holds every step ever created during the search. Growing it is
    // just a push_back of a small fixed-size struct - nothing here ever copies
    // a path, unlike the old State{visited_sequence, jump_sequence} copies.
    vector<Node> pool;
    pool.push_back({0, treasures_[0], -1, 0});

    int best_leaf = -1;       // no leaf found yet
    ll best_total = LLONG_MIN;

    stack<int> traversal_stack; // stack of pool indices, not full states
    traversal_stack.push(0);

    while (!traversal_stack.empty()) {
        int current = traversal_stack.top();
        traversal_stack.pop();
        bool has_next = false;
        // Explore all possible next jump options
        for (int jump : options_) {
            int next_index = pool[current].idx + jump;
            // Skip out of bound next jumps
            if (next_index  < 0 || next_index >= (int)treasures_.size()) {continue;}
            // Now its guaranteed to have next jumps
            has_next = true;
            // Record the next step as a child of "current" - O(1), no path copy
            pool.push_back({
                next_index,
                pool[current].total + treasures_[next_index],
                current, 
                jump}
            );
            traversal_stack.push((int)pool.size() - 1);
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
    }
    return build_result(pool, best_leaf);
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


Result max_treasure_BFS_queue(const vector<int> &treasures_, const vector<int> &options_) {
    // Same fix as DFS_stack: a node pool of parent-linked steps instead of a
    // queue full of self-contained states each hauling a full path copy.
    vector<Node> pool;
    pool.push_back({0, treasures_[0], -1, 0});

    int best_leaf = -1;
    ll best_total = LLONG_MIN;

    queue<int> traversal_queue; // queue of pool indices, not full states
    traversal_queue.push(0);

    while (!traversal_queue.empty()) {
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
                jump});
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
    }
    return build_result(pool, best_leaf);
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
