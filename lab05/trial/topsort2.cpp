
#include <bits/stdc++.h>
using namespace std;

template <typename Vertex, typename SourceCompare = less<Vertex>>
class TopologicalOrderGenerator {
public:
    using AdjacencyList = vector<vector<Vertex>>;

    TopologicalOrderGenerator(
        const vector<Vertex>& vertices,
        const AdjacencyList& outgoing,
        SourceCompare sourceCompare = SourceCompare{},
        bool sortSources = true,
        ostream& output = cout
    )
        : vertices_(vertices),
          sourceCompare_(sourceCompare),
          sortSources_(sortSources),
          output_(output),
          outgoing_(vertices.size()),
          indegree_(vertices.size(), 0),
          used_(vertices.size(), false)
    {
        const size_t n = vertices_.size();

        if (outgoing.size() != n) {
            throw invalid_argument("Adjacency list size mismatch.");
        }

        // Map each vertex label to its internal index.
        map<Vertex, size_t> index;

        for (size_t i = 0; i < n; ++i) {
            if (!index.emplace(vertices_[i], i).second) {
                throw invalid_argument("Vertex labels must be unique.");
            }
        }

        // Convert label-based edges to index-based edges.
        // outgoing[u] contains vertices reachable directly from u.
        for (size_t u = 0; u < n; ++u) {
            for (const Vertex& neighbor : outgoing[u]) {
                auto it = index.find(neighbor);

                if (it == index.end()) {
                    throw invalid_argument("Unknown neighbor vertex.");
                }

                size_t v = it->second;

                outgoing_[u].push_back(v);
                ++indegree_[v];
            }
        }

        order_.reserve(n);
    }

    // Prints every valid topological ordering as it is generated.
    void run() {
        backtrack();
    }

private:
    const vector<Vertex>& vertices_;
    SourceCompare sourceCompare_;
    bool sortSources_;
    ostream& output_;

    // Internal graph representation uses indices.
    vector<vector<size_t>> outgoing_;
    vector<size_t> indegree_;
    vector<bool> used_;

    // Stores only the current partial ordering.
    vector<size_t> order_;

    void printCurrentOrder() {
        for (size_t i = 0; i < order_.size(); ++i) {
            if (i > 0) {
                output_ << ' ';
            }

            output_ << vertices_[order_[i]];
        }

        output_ << '\n';
    }

    void backtrack() {
        const size_t n = vertices_.size();

        // A complete topological ordering has been generated.
        if (order_.size() == n) {
            printCurrentOrder();
            return;
        }

        // Find every currently available source.
        vector<size_t> sources;

        for (size_t u = 0; u < n; ++u) {
            if (!used_[u] && indegree_[u] == 0) {
                sources.push_back(u);
            }
        }

        // Control the order in which alternative sources are explored.
        if (sortSources_) {
            stable_sort(
                sources.begin(),
                sources.end(),
                [&](size_t a, size_t b) {
                    return sourceCompare_(
                        vertices_[a], vertices_[b]
                    );
                }
            );
        }

        // Explore every possible source choice.
        for (size_t u : sources) {
            used_[u] = true;
            order_.push_back(u);

            // Temporarily remove u and its outgoing edges.
            for (size_t v : outgoing_[u]) {
                --indegree_[v];
            }

            backtrack();

            // Restore the graph before exploring the next choice.
            for (size_t v : outgoing_[u]) {
                ++indegree_[v];
            }

            order_.pop_back();
            used_[u] = false;
        }
    }
};

int main() {
    vector<char> vertices = {'A', 'B', 'C', 'D'};

    // outgoing[i] contains the vertices reached by edges
    // leaving vertices[i].
    vector<vector<char>> outgoing = {
        {'C'},  // A -> C
        {'C'},  // B -> C
        {'D'},  // C -> D
        {}      // D has no outgoing edges
    };

    TopologicalOrderGenerator<char> generator(
        vertices, outgoing
    );

    generator.run();
}