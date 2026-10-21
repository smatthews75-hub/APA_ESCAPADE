#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Comparator = less<T>>
void TopDownParentDominance(vector<T>& heap, size_t current_idx, size_t heapSize, Comparator comp = Comparator()) {
    // TC BEST CASE  : already parent dominance, no swaps, exit : Omega(1)
    // TC WORST CASE : always NOT parent dominance, always swap "log n" tree depth times: O(log n)

    T target = std::move(heap[current_idx]);// Extract target, leaving a "hole" at current_idx

    size_t child = 2*current_idx + 1;// Left child 

    while (child < heapSize) {
        // Find "most extreme" child according to the comparator.
        // less() is left_child < right_child       -> right child should be prioritized.
        // greater() is left_child > right_child    -> right child should be prioritized.
        if (child + 1 < heapSize && comp(heap[child], heap[child + 1])) child++;// 2*i + 2

        // Check for dominance DOWNWARDS
        // less() is target < child     -> if target >= child
        // greater() is target > child  -> if target <= child
        // the dominance property is satisfied. break.
        if (!comp(target, heap[child])) break;

        // Move the child UP to fill the hole
        heap[current_idx] = std::move(heap[child]);
        
        current_idx = child; // Becomes parent for next child if exists
        child = 2 * current_idx + 1; // Left child of current node
    }

    // Drop the target into the final hole, dominant position
    heap[current_idx] = std::move(target);
}

void solve() {
    int N, i; cin >> N >> i; i--;
    vector<int> A(N);
    for (int &x: A) {cin >> x;}
    TopDownParentDominance(A, i, N, greater<int>());
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