#include <bits/stdc++.h>
using namespace std;


template <typename T, typename Comparator = less<T>>
void BottomUpParentDominance(vector<T>& heap, size_t current_idx, Comparator comp = Comparator()) {
    // TC BEST CASE  : already parent dominance, no swaps, exit : Omega(1)
    // TC WORST CASE : always NOT parent dominance, always swap "log n" tree depth times: O(log n)

    if (current_idx == 0) return; // idx 0 root has no parent

    T target = std::move(heap[current_idx]);// Extract target, leaving a "hole" at current_idx
    
    // Calculate initial parent index
    size_t parent = (current_idx - 1) / 2;

    // Traverse UP the tree
    // less() is parent < target     -> if dominance not yet enforced
    // greater() is parent > target  -> if dominance not yet enforced
    // comp() evaluates if the parent is "weaker" than the target child.
    while (current_idx > 0 && comp(heap[parent], target)) {
        // Move the weaker parent DOWN into the hole
        heap[current_idx] = std::move(heap[parent]);

        current_idx = parent; // Becomes child of next parent if exists
        
        if (current_idx == 0) break; // Prevent integer underflow on size_t when current_idx hits 0
        parent = (current_idx - 1) / 2; // Parent of current node
    }

    // Drop the target into the final hole, dominant position
    heap[current_idx] = std::move(target);
}


void solve() {
    int N, i; cin >> N >> i; i--;
    vector<int> A(N);
    for (int &x: A) {cin >> x;}
    BottomUpParentDominance(A, i, greater<int>());
    for (int &x: A) {cout << x << " ";}
    cout << "\n";
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