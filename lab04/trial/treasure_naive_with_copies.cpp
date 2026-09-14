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

struct State {
    int idx;
    ll total;
    vector<int> visited_sequence;
    vector<int> jump_sequence;
};

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
    Result best_res;
    stack<State> traversal_stack;
    traversal_stack.push({
        0, treasures_[0], 
        {0}, 
        {}
    });

    while (!traversal_stack.empty()) {
        State current = traversal_stack.top();
        traversal_stack.pop();
        bool has_next = false;
        // Explore all possible next jump options
        for (int jump : options_) {
            int next_index = current.idx + jump;
            // Skip out of bound next jumps
            if (next_index  < 0 || next_index >= (int)treasures_.size()) {continue;}
            // Now its guaranteed to have next jumps
            has_next = true;
            // Create the next state to be evaluated
            State next_state = current;
            next_state.idx = next_index;
            next_state.total += treasures_[next_index];
            next_state.visited_sequence.push_back(next_index);
            next_state.jump_sequence.push_back(jump);
            traversal_stack.push(next_state);
        }
        // If it reaches a child node where it cant jump anywhere else
        if (!has_next) {
            update_best_res(
                best_res, 
                current.visited_sequence, 
                current.jump_sequence, 
                current.total
            );
        }
    }
    return best_res;
}


Result max_treasure_DFS_recursive(const vector<int> &treasures_, const vector<int> &options_) {
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
    Result best_res;
    queue<State> traversal_queue; // Literally just change the stack into a queue from DFS
    traversal_queue.push({0, treasures_[0], {0}, {}});

    while (!traversal_queue.empty()) {
        State current = traversal_queue.front();
        traversal_queue.pop();
        bool has_next = false;
        // Explore all possible next jump options
        for (int jump : options_) {
            int next_index = current.idx + jump;
            // Skip out of bound next jumps
            if (next_index  < 0 || next_index >= (int)treasures_.size()) {continue;}
            // Now its guaranteed to have next jumps
            has_next = true;
            // Create the next state to be evaluated
            State next_state = current;
            next_state.idx = next_index;
            next_state.total += treasures_[next_index];
            next_state.visited_sequence.push_back(next_index);
            next_state.jump_sequence.push_back(jump);
            traversal_queue.push(next_state);
        }
        // If it reaches a child node where it cant jump anywhere else
        if (!has_next) {
            update_best_res(
                best_res,
                current.visited_sequence,
                current.jump_sequence,
                current.total
            );
        }
    }
    return best_res;
}


Result max_treasure_BFS_recursive(const vector<int> &treasures_, const vector<int> &options_) {
    Result best_res;
    queue<State> traversal_queue; // The recursion is LITERALLY JUST for traversing and managing the queue
    traversal_queue.push({0, treasures_[0], {0}, {}});

    function<void()> BFS_process_queue =
    [&best_res, &BFS_process_queue, &treasures_, &options_, &traversal_queue]
    (){
        // Base case to stop recursion
        if (traversal_queue.empty()) {return;}
        // BASICALLY QUEUE PROCESSING LITERALLY ONE TO ONE
        State current = traversal_queue.front();
        traversal_queue.pop();
        bool has_next = false;
        // Explore all possible next jump options
        for (int jump : options_) {
            int next_index = current.idx + jump;
            // Skip out of bound next jumps
            if (next_index  < 0 || next_index >= (int)treasures_.size()) {continue;}
            // Now its guaranteed to have next jumps
            has_next = true;
            // Create the next state to be evaluated
            State next_state = current;
            next_state.idx = next_index;
            next_state.total += treasures_[next_index];
            next_state.visited_sequence.push_back(next_index);
            next_state.jump_sequence.push_back(jump);
            traversal_queue.push(next_state);
        }
        // If it reaches a child node where it cant jump anywhere else
        if (!has_next) {
            update_best_res(
                best_res,
                current.visited_sequence,
                current.jump_sequence,
                current.total
            );
        }
        // Continue the recursion to continue processing the queue
        BFS_process_queue();
    };

    BFS_process_queue();
    return best_res;
}