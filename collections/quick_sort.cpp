#include <iostream>
#include <vector>
#include <utility>
#include <functional>

// Optimizes pivot selection to avoid O(N^2) worst-case performance on sorted arrays
template <typename T, typename Compare>
void place_median_of_three_at_end(std::vector<T>& arr, size_t left, size_t mid, size_t right_inclusive, Compare comp) {
    if (comp(arr[mid], arr[left])) std::swap(arr[left], arr[mid]);
    if (comp(arr[right_inclusive], arr[left])) std::swap(arr[left], arr[right_inclusive]);
    if (comp(arr[mid], arr[right_inclusive])) std::swap(arr[mid], arr[right_inclusive]);
    // The median is now safely positioned at the right_inclusive index
}

// Lomuto partition scheme adapted for [left, right)
template <typename T, typename Compare>
size_t partition(std::vector<T>& arr, size_t left, size_t right, Compare comp) {
    // Convert exclusive 'right' to inclusive for pivot targeting
    size_t right_inclusive = right - 1;
    size_t mid = left + (right - left) / 2;
    
    // Select a good pivot and move it to the end
    place_median_of_three_at_end(arr, left, mid, right_inclusive, comp);
    
    // We can use auto& to avoid copying large objects, but primitives copy fine
    const T& pivot = arr[right_inclusive];
    
    size_t i = left;
    for (size_t j = left; j < right_inclusive; ++j) {
        // If element is smaller than the pivot, swap it into the left partition
        if (comp(arr[j], pivot)) {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    
    // Move the pivot into its final, correctly sorted position
    std::swap(arr[i], arr[right_inclusive]);
    
    // Return the absolute index of the pivot
    return i;
}

// Internal recursive implementation using half-open intervals [left, right)
template <typename T, typename Compare>
void quick_sort_impl(std::vector<T>& arr, size_t left, size_t right, Compare comp) {
    // Base case: 0 or 1 elements are naturally sorted
    if (right - left <= 1) {
        return;
    }

    // Partition the array and get the final resting index of the pivot
    size_t pivot_idx = partition(arr, left, right, comp);

    // Recursively sort the left and right halves.
    // Notice how cleanly [left, right) handles the bounds:
    // We pass 'pivot_idx' as the right bound for the left half (it becomes exclusive).
    // We pass 'pivot_idx + 1' as the left bound for the right half.
    quick_sort_impl(arr, left, pivot_idx, comp);
    quick_sort_impl(arr, pivot_idx + 1, right, comp);
}

// Public interface defaulting to std::less<> (transparent comparator)
template <typename T, typename Compare = std::less<>>
void quick_sort(std::vector<T>& arr, Compare comp = Compare{}) {
    quick_sort_impl(arr, 0, arr.size(), comp);
}

int main() {
    std::vector<long long> data = {8, 3, 1, 7, 0, 10, 2};
    quick_sort(data);

    for (const auto& val : data) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}