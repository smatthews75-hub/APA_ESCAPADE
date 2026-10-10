#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <limits> // Needed for std::numeric_limits
#include <vector>
#include <random>

// Core search using half-open intervals [begin, end)
template<class T> 
size_t binary_search(const std::vector<T>& array, T target, size_t begin, size_t end) {
    // end can safely be array.size() because it is exclusive
    if (begin > end || end > array.size()) {
        throw std::invalid_argument("Search bounds are invalid or out of range.");
    }

    size_t low = begin;
    size_t high = end; 

    // Changed from (low <= high) to (low < high)
    while (low < high) { 
        size_t mid = low + (high - low) / 2;

        if (array[mid] == target) return mid;

        if (array[mid] < target) {
            low = mid + 1; 
        } else {
            // NO MINUS ONE! If target is smaller, the new exclusive bound is mid.
            // Even if mid is 0, high becomes 0, and the loop safely terminates.
            high = mid; 
        }
    }
    
    // The standard way to return "not found" when returning an unsigned size_t
    return std::numeric_limits<size_t>::max(); 
}

// The Overload
template<class T> 
size_t binary_search(const std::vector<T>& array, T target) {
    // Passes array.size() directly. No need for size() - 1!
    return binary_search(array, target, 0, array.size());
}

int main() {
    std::random_device rd;     
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> randint(-100, 100);
    std::uniform_real_distribution<float> randfloat(-100.0, 100.0);

    int n_; std::cin >> n_;

    std::vector<int> A(n_, 0);
    std::vector<float> B(n_, 0.0);
    for (int i = 0; i < n_; i++) {
        A[i] = randint(gen);
        B[i] = std::round(randfloat(gen) * 100.0) / 100.0;
    }
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());

    for (int i = 0; i < n_; i++) {std::cout << A[i] << " ";}
    std::cout << std::endl;
    for (int i = 0; i < n_; i++) {std::cout << B[i] << " ";}
    std::cout << std::endl;

    while (true) {
        int int_target; std::cin >> int_target;
        float float_target; std::cin >> float_target;

        size_t int_result = binary_search(A, int_target);
        
        if (int_result != std::numeric_limits<size_t>::max()) {
            std::cout << "Integer " << int_target << " found at index: " << int_result << "|" << A[int_result] << "\n";
        } else {
            std::cout << "Integer " << int_target << " not found.\n";
        }

        size_t float_result = binary_search(B, float_target);
        
        if (float_result != std::numeric_limits<size_t>::max()) {
            std::cout << "Double " << float_target << " found at index: " << float_result << "|" << B[float_result] << "\n";
        } else {
            std::cout << "Double " << float_target << " not found.\n";
        }
    }
    
    return 0;
}