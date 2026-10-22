#include <bits/stdc++.h>
using namespace std;

#define ll long long

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
template <typename T, typename Compare>
void quick_sort(std::vector<T>& arr, Compare comp = Compare{}) {
    quick_sort_impl(arr, 0, arr.size(), comp);
}

struct Person {
    float height;
    string name;
};

struct Candidate {
    Person boy;
    Person girl;
};

void solve() {
    int N, M; cin >> N >> M;
    vector<Person> boys(N);
    vector<Person> girls(M);
    string name; float height;
    // for (int i = 0; i < N; i++) {
    //     cin >> name >> height;
    //     boys[i] = {height, name};
    // }
    // for (int i = 0; i < M; i++) {
    //     cin >> name >> height;
    //     girls[i] = {height, name};
    // }
    for (Person &p : boys) {
        cin >> name >> height;
        p = {height, name};
    }
    for (Person &p : girls) {
        cin >> name >> height;
        p = {height, name};
    }
    auto compPerson = [](const Person &a, const Person &b){
        return (a.height == b.height) ? a.name < b.name : a.height < b.height;
    };

    quick_sort(boys, compPerson);
    quick_sort(girls, compPerson);

    // for (Person &p : boys) {cout << p.name << " ";}
    // cout << "\n" << endl;
    // for (Person &p : girls) {cout << p.name << " ";}
    // cout << "\n" << endl;
    int b = 0, g = 0, size_b = boys.size(), size_g = girls.size();

    float least_diff = 1e9;
    vector<Candidate> candidates; candidates.reserve(10);
    while (b < size_b && g < size_g) {
        float boy_height = boys[b].height;
        float girl_height = girls[g].height;
        float diff = abs(boy_height - girl_height);

        if (diff < least_diff - 1e-3) {
            least_diff = diff;
            candidates = {{boys[b], girls[g]}};
        } else if (abs(diff - least_diff) <= 1e-3) { // diff == least_diff
            candidates.push_back({boys[b], girls[g]});
        }
        if (boy_height < girl_height) {b++; continue;}
        else {g++; continue;}
    }

    // cout << candidates.size() << "\n" << endl;
    if (candidates.size() == 1) {
        cout << candidates[0].boy.name << " " << candidates[0].girl.name << "\n";
    } else {
        auto compCandidate = [](const Candidate &aa, const Candidate &bb){
            if (aa.boy.name == bb.boy.name) {
                return aa.girl.name < bb.girl.name;
            } else {
                return aa.boy.name < bb.boy.name;
            }
        };
        quick_sort(candidates, compCandidate);
        cout << candidates[0].boy.name << " " << candidates[0].girl.name << "\n";
    }
}
/*
5 4
erdos 185.32
graham 153.91
szemeredy 171.03
tutte 164.28
seymour 182.01
noether 161.42
chudnovsky 175.82
fanchung 155.90
szekeres 161.51
*/

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