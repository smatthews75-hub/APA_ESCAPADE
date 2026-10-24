// Topological sort (Kahn's algorithm) on an adjacency list.
// - Accepts any directed graph; reports a clear error if a cycle exists.
// - Source finding is O(1) amortised via a queue of in-degree-0 vertices.
// - Removing a vertex v costs O(deg(v)): decrement in-degree of its successors.
// - Total time O(V + E).
//
// Input format (stdin):
//   n                      number of vertices (labelled 0..n-1)
//   then n lines, one per vertex i:  k s1 s2 ... sk
//                          k = out-degree of i, s* = successors of i
//
// Example (the slide's DAG: 1->0, 3->0, 0->2, 1->2, 1->4, 2->4, 3->4):
//   5
//   1 2
//   3 0 2 4
//   1 4
//   2 0 4
//   0
#include <bits/stdc++.h>
using namespace std;

using AdjList = vector<vector<int>>;

struct TopoResult {
    bool ok = false;
    vector<int> order;  // valid topological order when ok == true
    vector<int> cycle;  // one concrete cycle (v0 -> v1 -> ... -> v0) when ok == false
    vector<int> blocked; // all vertices that could not be ordered (on or behind a cycle)
};

// Finds one concrete cycle among the vertices Kahn's algorithm could not remove.
// Every remaining vertex has in-degree > 0 from other remaining vertices, so
// walking backwards through predecessors must eventually revisit a vertex.
static vector<int> extractCycle(const AdjList& adj, const vector<bool>& removed) {
    const int n = static_cast<int>(adj.size());
    vector<int> pred(n, -1);
    int start = -1;
    for (int u = 0; u < n; ++u) {
        if (removed[u]) continue;
        if (start == -1) start = u;
        for (int v : adj[u])
            if (!removed[v]) pred[v] = u;
    }
    if (start == -1) return {};

    vector<int> seenAt(n, -1);
    vector<int> walk;
    int cur = start;
    while (seenAt[cur] == -1) {
        seenAt[cur] = static_cast<int>(walk.size());
        walk.push_back(cur);
        cur = pred[cur];
    }
    // walk[seenAt[cur]..] is the cycle in backward order; reverse to forward order.
    vector<int> cycle(walk.begin() + seenAt[cur], walk.end());
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

TopoResult topologicalSort(const AdjList& adj) {
    const int n = static_cast<int>(adj.size());

    // Validate edges and compute in-degrees.
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            if (v < 0 || v >= n)
                throw invalid_argument("edge " + to_string(u) + " -> " +
                    to_string(v) + " references a vertex outside [0, " +
                    to_string(n - 1) + "]");
            ++indeg[v];
        }
    }

    // Sources = vertices with in-degree 0.
    queue<int> q;
    for (int v = 0; v < n; ++v) if (indeg[v] == 0) q.push(v);

    TopoResult res;
    vector<bool> removed(n, false);

    while (!q.empty()) {
        int v = q.front();  // FindSource(D)
        q.pop();
        res.order.push_back(v);  // print(v)
        removed[v] = true;
        for (int w : adj[v])  // D = D - {v}
            if (--indeg[w] == 0) q.push(w);
    }

    if (static_cast<int>(res.order.size()) == n) {
        res.ok = true;
        return res;
    }

    for (int v = 0; v < n; ++v) if (!removed[v]) res.blocked.push_back(v);
    res.cycle = extractCycle(adj, removed);
    return res;
}

static void printError(const TopoResult& r) {
    cerr << "ERROR: graph contains a cycle - topological order does not exist.\n";
    if (!r.cycle.empty()) {
        cerr << "  Cycle found: ";
        for (int v : r.cycle) cerr << v << " -> ";
        cerr << r.cycle.front() << "\n";
    }
    cerr << "  Vertices that could not be ordered (" << r.blocked.size() << "): ";
    for (size_t i = 0; i < r.blocked.size(); ++i)
        cerr << (i ? ", " : "") << r.blocked[i];
    cerr << "\n";
}

int main() {
    int n;
    if (!(cin >> n) || n < 0) {
        cerr << "ERROR: expected a non-negative vertex count.\n";
        return 2;
    }

    AdjList adj(n);
    for (int i = 0; i < n; ++i) {
        int k;
        if (!(cin >> k) || k < 0) {
            cerr << "ERROR: bad out-degree for vertex " << i << ".\n";
            return 2;
        }
        adj[i].resize(k);
        for (int j = 0; j < k; ++j) {
            if (!(cin >> adj[i][j])) {
                cerr << "ERROR: missing successor for vertex " << i << ".\n";
                return 2;
            }
        }
    }

    try {
        TopoResult r = topologicalSort(adj);
        if (!r.ok) {
            printError(r);
            return 1;
        }
        cout << "Topological order:";
        for (int v : r.order) cout << ' ' << v;
        cout << '\n';
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << '\n';
        return 2;
    }
    return 0;
}
