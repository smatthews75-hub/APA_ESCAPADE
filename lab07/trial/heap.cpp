#include <iostream>
#include <random>
#include <vector>
#include <iostream>
#include <functional> // For less, greater
#include <utility>    // For std::move

#define ll long long

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

template <typename T, typename Compare = less<T>>
void TopDownHeapify(vector<T>& arr, Compare comp = Compare()) {
    // TC BEST & WORST CASE is n times parent dominance
    // MAXHEAP use less() <- default
    // MINHEAP use greater()
    ll n = arr.size();
    for (ll i = (n / 2) - 1; i >= 0; i--) {// Parent nodes from highest idx
        TopDownParentDominance(arr, i, n, comp);
        cout << "idx " << i << ": ";
        for (T val : arr) cout << val << " ";
        cout << "\n";
    }
}

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

// Helper to build the heap
template <typename T, typename Compare = less<T>>
void BottomUpHeapify(vector<T>& arr, Compare comp = Compare()) {
    // TC BEST & WORST CASE is n times parent dominance
    // MAXHEAP use less() <- default
    // MINHEAP use greater()
    ll n = arr.size();
    // Conceptually "inserts" each element into an existing valid sub-heap.
    for (ll i = 1; i < n; i++) {
        BottomUpParentDominance(arr, i, comp);
        cout << "idx " << i << ": ";
        for (T val : arr) cout << val << " ";
        cout << "\n";
    }
}

template<typename T, typename Compare = less<T>>
void heap_push_insert(vector<T> &heap, T new_item, Compare comp = Compare()) {
    // MAXHEAP use less() <- default
    // MINHEAP use greater()
    heap.push_back(std::move(new_item));
    BottomUpParentDominance(heap, heap.size() - 1, comp);
}

template<typename T, typename Compare = std::less<T>>
T heap_pop_delete(std::vector<T> &heap, Compare comp = Compare()) {
    // MAXHEAP use less() <- default
    // MINHEAP use greater()
    if (heap.empty()) throw std::out_of_range("Cannot pop from an empty heap");

    T popped_item = std::move(heap[0]);

    if (heap.size() == 1) {
        heap.pop_back();
        return popped_item;
    }

    heap[0] = std::move(heap.back());
    heap.pop_back();

    TopDownParentDominance(heap, 0, heap.size(), comp);

    return popped_item;
}


int main(void) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randint(-100, 100);
    uniform_real_distribution<float> randfloat(-100.0, 100.0);
    size_t n; cin >> n;
    vector<int> A(n);
    vector<float> B(n);
    for (int &x : A) x = randint(gen);
    for (float &x : B) x = randfloat(gen);

    vector<int> MAXHEAP = {1, 3, 5, 7, 9, 11, 13};
    vector<float> MINHEAP = {13, 11, 9, 7, 5, 3, 1};
    vector<int> MAXHEAP_ = {1, 3, 5, 7, 9, 11, 13};
    vector<float> MINHEAP_ = {13, 11, 9, 7, 5, 3, 1};
    // vector<int> MAXHEAP = A;
    // vector<float> MINHEAP = B;
    // vector<int> MAXHEAP_ = A;
    // vector<float> MINHEAP_ = B;
    cout << "\nTOP DOWN MAX HEAP\n       ";
    for (int val : MAXHEAP) cout << val << " ";
    cout << "\n";
    TopDownHeapify(MAXHEAP, less<int>());
    cout << "Max-Heap (less): ";
    for (int val : MAXHEAP) cout << val << " ";
    cout << "\n";

    // heap_push_insert(MAXHEAP, 15, less<int>());
    // for (int val : MAXHEAP) cout << val << " "; 
    // cout << "\n";
    cout << heap_pop_delete(MAXHEAP, less<int>()) << "\n";
    for (int val : MAXHEAP) cout << val << " "; 
    cout << "\n\n";



    cout << "\nTOP DOWN MIN HEAP\n       ";
    for (float val : MINHEAP) cout << val << " ";
    cout << "\n";
    TopDownHeapify(MINHEAP, greater<float>());
    cout << "Min-Heap (greater): ";
    for (float val : MINHEAP) cout << val << " ";
    cout << "\n";

    // heap_push_insert(MINHEAP, 0.0f, greater<float>());
    // for (float val : MINHEAP) cout << val << " "; 
    // cout << "\n";
    cout << heap_pop_delete(MINHEAP, greater<float>()) << "\n\n";
    for (float val : MINHEAP) cout << val << " "; 
    cout << "\n\n";



    cout << "\nBOTTOM UP MAX HEAP\n       ";
    for (int val : MAXHEAP_) cout << val << " ";
    cout << "\n";
    BottomUpHeapify(MAXHEAP_, less<int>());
    cout << "Max-Heap (less): ";
    for (int val : MAXHEAP_) cout << val << " ";
    cout << "\n";

    // heap_push_insert(MAXHEAP_, 15, less<int>());
    // for (int val : MAXHEAP_) cout << val << " "; 
    // cout << "\n";
    cout << heap_pop_delete(MAXHEAP_, less<int>()) << "\n\n";
    for (int val : MAXHEAP_) cout << val << " "; 
    cout << "\n\n";



    cout << "\nBOTTOM UP MIN HEAP\n       ";
    for (float val : MINHEAP_) cout << val << " ";
    cout << "\n";
    BottomUpHeapify(MINHEAP_, greater<float>());
    cout << "Min-Heap (greater): ";
    for (float val : MINHEAP_) cout << val << " ";
    cout << "\n";

    // heap_push_insert(MINHEAP_, 0.0f, greater<float>());
    // for (float val : MINHEAP_) cout << val << " "; 
    // cout << "\n";
    cout << heap_pop_delete(MINHEAP_) << "\n\n";
    for (float val : MINHEAP_) cout << val << " "; 
    cout << "\n\n";
    // 3. Custom Lambda Comparator (e.g., sort by absolute value descending)
    // vector<int> customData = {-10, 2, 7, -3, 8};
    // auto absCompare = [](int a, int b) {
    //     return abs(a) < abs(b); 
    // };
    
    // TopDownHeapify(customData, absCompare);
    
    // cout << "Custom-Heap (Abs Max): ";
    // for (int val : customData) cout << val << " ";
    // cout << "\n";

    return 0;
}