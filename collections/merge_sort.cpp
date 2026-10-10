#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <functional>

// Internal recursive implementation using half-open intervals [left, right)
template <typename T, typename Compare>
void merge_sort_impl(std::vector<T>& arr, std::vector<T>& temp, size_t left, size_t right, Compare comp) {
    // Base case: 0 or 1 elements are already sorted
    if (right - left <= 1) {
        return;
    }

    // Compute mid-point safely avoiding size_t overflow
    size_t mid = left + (right - left) / 2;

    merge_sort_impl(arr, temp, left, mid, comp);
    merge_sort_impl(arr, temp, mid, right, comp);

    size_t i = left;
    size_t j = mid;
    size_t k = left;

    // Merge the two halves into the temp buffer
    while (i < mid && j < right) {
        // comp(arr[j], arr[i]) guarantees stable sorting. 
        // If elements are equivalent, the left element (i) takes precedence.
        if (comp(arr[j], arr[i])) {
            temp[k++] = std::move(arr[j++]);
        } else {
            temp[k++] = std::move(arr[i++]);
        }
    }

    // Consume any remaining elements from the left subarray
    while (i < mid) {
        temp[k++] = std::move(arr[i++]);
    }
    
    // Consume any remaining elements from the right subarray
    while (j < right) {
        temp[k++] = std::move(arr[j++]);
    }

    // Move the merged sequence back to the original array
    for (size_t idx = left; idx < right; ++idx) {
        arr[idx] = std::move(temp[idx]);
    }
}

// Public interface defaulting to std::less<> (transparent comparator)
template <typename T, typename Compare = std::less<>>
void merge_sort(std::vector<T>& arr, Compare comp = Compare{}) {
    if (arr.size() <= 1) {
        return;
    }
    
    // Pre-allocate auxiliary memory ONCE to eliminate allocation overhead during recursion
    std::vector<T> temp(arr.size());
    merge_sort_impl(arr, temp, 0, arr.size(), comp);
}

// --- Demonstration Data Structures ---

struct Player {
    std::string name;
    long long score;
};

int main() {
    // 1. Sorting standard primitives (Ascending)
    std::vector<long long> numbers = {38, 27, 43, 3, 9, 82, 10};
    merge_sort(numbers);
    
    std::cout << "Numbers: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << "\n\n";

    // 2. Sorting with a custom comparator (Descending)
    std::vector<double> floats = {3.14, 2.71, 1.61, 0.57, 4.66};
    merge_sort(floats, std::greater<double>());
    
    std::cout << "Floats (descending): ";
    for (const auto& f : floats) std::cout << f << " ";
    std::cout << "\n\n";

    // 3. Sorting custom structs via lambda (Sorting Players by score descending, then name)
    std::vector<Player> leaderboard = {
        {"Alice", 1500},
        {"Bob", 2200},
        {"Charlie", 1500},
        {"Dave", 3100}
    };

    merge_sort(leaderboard, [](const Player& a, const Player& b) {
        if (a.score == b.score) {
            return a.name < b.name; // Tie-breaker: alphabetical order
        }
        return a.score > b.score;   // Primary: highest score first
    });

    std::cout << "Leaderboard:\n";
    for (const auto& p : leaderboard) {
        std::cout << p.name << " (" << p.score << ")\n";
    }

    return 0;
}