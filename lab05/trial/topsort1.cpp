#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

template <typename T>
class TopologicalSorter {
public:
    // Method 1: Strict compliance with the course material using a Queue.
    // Time Complexity: O(V + E) as recommended in the screenshot.
    static void printWithQueue(const std::unordered_map<T, std::vector<T>>& adjList) {
        auto inDegree = computeInDegrees(adjList);
        std::queue<T> sources;

        // Initialize sources container
        for (const auto& [node, degree] : inDegree) {
            if (degree == 0) sources.push(node);
        }

        // while D is not empty
        while (!sources.empty()) {
            T v = sources.front(); // v = FindSource(D)
            sources.pop();
            
            std::cout << v << " "; // print(v) - printing on the go

            // D = D - {v}
            // Logically removes node v by decrementing the in-degree of its neighbors
            if (adjList.count(v)) {
                for (const T& neighbor : adjList.at(v)) {
                    if (--inDegree[neighbor] == 0) { 
                        sources.push(neighbor);
                    }
                }
            }
        }
        std::cout << "\n";
    }

    // Method 2: Custom Sequence Control using a Priority Queue.
    // Time Complexity: O(V + E log V) due to sorting overhead.
    template <typename Compare = std::less<T>>
    static void printWithCustomSort(const std::unordered_map<T, std::vector<T>>& adjList, Compare comp = Compare()) {
        auto inDegree = computeInDegrees(adjList);
        
        // Priority Queue dynamically sorts available sources based on the Compare functor
        std::priority_queue<T, std::vector<T>, Compare> sources(comp);

        for (const auto& [node, degree] : inDegree) {
            if (degree == 0) sources.push(node);
        }

        while (!sources.empty()) {
            T v = sources.top(); 
            sources.pop();
            
            std::cout << v << " "; 

            if (adjList.count(v)) {
                for (const T& neighbor : adjList.at(v)) {
                    if (--inDegree[neighbor] == 0) {
                        sources.push(neighbor);
                    }
                }
            }
        }
        std::cout << "\n";
    }

private:
    // Helper to calculate initial in-degrees (derajat masuk)
    static std::unordered_map<T, int> computeInDegrees(const std::unordered_map<T, std::vector<T>>& adjList) {
        std::unordered_map<T, int> inDegree;
        
        // Ensure all nodes, including those with 0 outgoing edges, are tracked
        for (const auto& [u, neighbors] : adjList) {
            if (inDegree.find(u) == inDegree.end()) inDegree[u] = 0;
            for (const T& v : neighbors) {
                inDegree[v]++;
            }
        }
        return inDegree;
    }
};

int main() {
    // Example 1: Integer Graph 
    std::unordered_map<int, std::vector<int>> intGraph = {
        {0, {1, 3}},
        {1, {}},
        {2, {0, 1}},
        {3, {}},
        {4, {1, 2, 3}}
    };

    std::cout << "Integer Graph (Standard Queue / BFS-like): ";
    TopologicalSorter<int>::printWithQueue(intGraph);

    // Forces numerically largest available source to be processed first
    std::cout << "Integer Graph (Custom Priority Queue - Descending): ";
    TopologicalSorter<int>::printWithCustomSort(intGraph, std::less<int>());


    // Example 2: Character Graph
    std::unordered_map<char, std::vector<char>> charGraph = {
        {'A', {'C'}},
        {'B', {'C', 'D'}},
        {'C', {'E'}},
        {'D', {'F'}},
        {'E', {'H', 'F'}},
        {'F', {'G'}},
        {'G', {}},
        {'H', {}}
    };

    std::cout << "\nCharacter Graph (Standard Queue / BFS-like): ";
    TopologicalSorter<char>::printWithQueue(charGraph);

    // Forces alphabetically earliest available source to be processed first
    std::cout << "Character Graph (Custom Priority Queue - Ascending): ";
    TopologicalSorter<char>::printWithCustomSort(charGraph, std::greater<char>());

    return 0;
}