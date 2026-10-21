#include <bits/stdc++.h>
using namespace std;

template <typename T>
class HospitalQueue {
private:
    struct Element {
        size_t sequence_id;
        int priority;
        T data;
    };
    vector<Element> heap;
    size_t sequence_id = 0;
    
    bool comp(Element &a, Element &b) {
        if (a.priority == b.priority) {
            // Tie-breaker: Smaller sequence_id is prioritized.
            // By returning 'true' when a > b, we force the smaller ID to the top.
            return a.sequence_id > b.sequence_id;
        }
        // Standard max heap behavior: larger priority goes to the top.
        return a.priority < b.priority;
    }

    void TopDownParentDominance(size_t current_idx, size_t heapSize) {
        // TC BEST CASE  : already parent dominance, no swaps, exit : Omega(1)
        // TC WORST CASE : always NOT parent dominance, always swap "log n" tree depth times: O(log n)
    
        Element target = std::move(heap[current_idx]);// Extract target, leaving a "hole" at current_idx
    
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
    
    void BottomUpParentDominance(size_t current_idx) {
        // TC BEST CASE  : already parent dominance, no swaps, exit : Omega(1)
        // TC WORST CASE : always NOT parent dominance, always swap "log n" tree depth times: O(log n)
    
        if (current_idx == 0) return; // idx 0 root has no parent
    
        Element target = std::move(heap[current_idx]);// Extract target, leaving a "hole" at current_idx
        
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
public:
    void push(T &new_item, int priority) {
        // MAXHEAP use less() <- default
        // MINHEAP use greater()
        Element new_element = {sequence_id++, priority, std::move(new_item)};
        heap.push_back(std::move(new_element));
        BottomUpParentDominance(heap.size() - 1);
    }

    bool not_empty() {
        return !heap.empty();
    }

    T pop() {
        // MAXHEAP use less() <- default
        // MINHEAP use greater()
        if (heap.empty()) throw std::out_of_range("Cannot pop from an empty heap");
    
        Element popped_item = std::move(heap[0]);
    
        if (heap.size() == 1) {
            heap.pop_back();
            return std::move(popped_item.data);
        }
    
        heap[0] = std::move(heap.back());
        heap.pop_back();
    
        TopDownParentDominance(0, heap.size());
    
        return std::move(popped_item.data);
    }
};


struct Patient {
    bool is_edwards;
};

// struct Patient {
//     bool is_edwards;
//     int age;
//     string name;
// };
/*
10
hadir bunyan 14
hadir luther 65
hadir owen 23
panggil
hadir knox 25
hadir edwards 23
panggil
hadir zwingli 71
panggil
hadir calvin 54
*/

void solve() {
    int k; cin >> k; string action, name;

    HospitalQueue<Patient> QUEUE;

    bool edwards_is_called = false;
    int queue = 0;


    for (int i = 0; i < k; i++) {
        cin >> action;
        if (action == "hadir") {
            cin >> name; int age; cin >> age;
            // Patient person = {name == "edwards", age, name};
            Patient person = {name == "edwards"};
            QUEUE.push(person, age);
        } else {
            Patient person = QUEUE.pop();
            if (person.is_edwards) edwards_is_called = true;
        }
    }

    if (edwards_is_called) {cout << queue << "\n"; return;}
    while (QUEUE.not_empty()) {
        Patient person = QUEUE.pop();
        // cout << person.name << "(" << person.age << ") ";
        queue++; if (person.is_edwards) break;
    }
    cout << queue << "\n";
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