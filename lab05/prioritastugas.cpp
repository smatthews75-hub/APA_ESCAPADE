// Lab05: Urutan Prioritas Tugas Proyek
//
// PROBLEM IN ONE LINE
//   Given N tasks and M prerequisite edges "A must come before B", print an
//   ordering that respects every edge. If several orderings exist, print the
//   LEXICOGRAPHICALLY SMALLEST one. If the edges contain a cycle, print MUSTAHIL.
//
// APPROACH: Kahn's algorithm (topological sort) with a MIN-HEAP
//   1. Compute the in-degree of every task (how many prerequisites it still waits on).
//   2. Every task with in-degree 0 is "available". Keep the available tasks in a
//      min-heap (priority_queue with greater<int>).
//   3. Repeatedly take the SMALLEST available task, append it to the answer, and
//      "complete" it: decrement the in-degree of each task that depends on it.
//      Any task that reaches in-degree 0 becomes available.
//   4. If fewer than N tasks were emitted, the rest sit on/behind a cycle -> MUSTAHIL.
//
// WHY THE MIN-HEAP GIVES THE LEXICOGRAPHICALLY SMALLEST ORDER (greedy argument)
//   The first element of the answer must be some task with no prerequisites, and
//   the smallest such task is the best possible first element. Picking it never
//   hurts: whatever remains is the same problem on a smaller graph. Applying that
//   argument at every position yields the lexicographically smallest sequence.
//   A plain FIFO queue does NOT do this: it emits tasks in the order they became
//   available, which is not the same as smallest-label-first.
//
//   Example where the FIFO version of the original code fails:
//       3 1
//       1 0
//     Available at start: {1, 2}. FIFO pops 1, then 0 becomes available and is
//     queued BEHIND 2, giving "1 2 0". The smallest valid order is "1 0 2"
//     (after 1, the available set is {0, 2} and 0 < 2).
//
// COMPLEXITY
//   Time  O((N + M) log N): each edge is relaxed once, each vertex enters/leaves the heap once.
//   Space O(N + M) for the adjacency list.
//   With N <= 1000 and M <= ~500,000 this is far below the limits.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // adj[a] = all tasks b that require task a first (edge a -> b).
    vector<vector<int>> adj(n);
    // indeg[b] = number of prerequisites of b not yet completed.
    vector<int> indeg(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b; // a -> b
        adj[a].push_back(b);
        ++indeg[b];
    }

    // Min-heap of currently available tasks (in-degree 0); top() is the smallest label.
    priority_queue<int, vector<int>, greater<int>> available;
    for (int v = 0; v < n; v++)
        if (indeg[v] == 0) available.push(v);

    vector<int> order;
    order.reserve(n);

    while (!available.empty()) {
        int v = available.top();   // smallest task we can do right now
        available.pop();
        order.push_back(v);

        // Finishing v satisfies one prerequisite of each successor.
        for (int w : adj[v])
            if (--indeg[w] == 0) available.push(w);
    }

    // A cycle keeps every task on it (and everything behind it) at in-degree > 0
    // forever, so they are never emitted and order.size() < n.
    if (static_cast<int>(order.size()) != n) {
        cout << "MUSTAHIL\n";
        return 0;
    }

    // Single spaces between numbers, no trailing space.
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
    return 0;
}
