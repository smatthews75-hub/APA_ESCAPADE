#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------------
// 1) Plain counting sort for non-negative integers (the textbook version)
//
//   Idea: instead of COMPARING elements, COUNT how many times each value
//   occurs, then rebuild the array from those counts.  No comparisons at all,
//   which is why it can beat the O(n log n) lower bound of comparison sorts.
//
//   Cost: O(n + k) time and O(n + k) memory, where k = max - min + 1
//   (the size of the key range).
// ---------------------------------------------------------------------------
vector<int> counting_sort_simple(const vector<int> &a, int max_value) {
    // count[v] = how many times v appears
    vector<int> count(max_value + 1, 0);
    for (int x : a) count[x]++;

    // rebuild: write each value count[v] times, in increasing order of v
    vector<int> result;
    result.reserve(a.size());
    for (int v = 0; v <= max_value; v++)
        for (int c = 0; c < count[v]; c++) result.push_back(v);
    return result;
}

// ---------------------------------------------------------------------------
// 2) Stable, generic counting sort (what you actually want in practice)
//
//   The simple version above only works for bare integers, because it throws
//   the original elements away and re-creates them from the counts.  If the
//   elements are records (a student with a grade, a pair, a struct...) we must
//   MOVE the original elements, and keep equal keys in their original order
//   (stability).  That needs the "prefix sum" step:
//
//       count[k]  -> how many elements have key k
//       prefix    -> count[k] becomes "index where the block of key k STARTS"
//       placement -> walk the input FORWARDS, put each element at
//                    count[key]++, so equal keys keep their input order.
//                    (The other common form walks backwards with --count[key]
//                    over "end" indices; both are stable.)
//
//   key_of : any callable T -> integer.  It replaces the comparator.
//   lo, hi : inclusive range the keys are guaranteed to lie in.
// ---------------------------------------------------------------------------
template <typename T, typename KeyFn>
vector<T> counting_sort(const vector<T> &a, KeyFn key_of, long long lo, long long hi,
                        bool descending = false) {
    size_t k = static_cast<size_t>(hi - lo + 1);  // number of distinct possible keys

    // map a key to its bucket; flipping the mapping gives descending order
    auto bucket = [&](const T &x) -> size_t {
        size_t b = static_cast<size_t>(static_cast<long long>(key_of(x)) - lo);
        return descending ? (k - 1 - b) : b;
    };

    vector<size_t> count(k + 1, 0);
    for (const T &x : a) count[bucket(x) + 1]++;          // histogram (shifted by 1)
    for (size_t i = 0; i < k; i++) count[i + 1] += count[i];
    // now count[b] = first output index for bucket b

    vector<T> out(a.size());
    for (const T &x : a) out[count[bucket(x)]++] = x;     // forward pass + "start index"
    // forward pass with start indices is also stable: earlier input -> earlier slot
    return out;
}

struct Student {
    string name;
    int grade;
};

int main() {
    // --- plain integers
    vector<int> nums = {4, 2, 2, 8, 3, 3, 1};
    for (int x : counting_sort_simple(nums, 8)) cout << x << ' ';
    cout << "\n";

    // --- negative numbers: just pass the real min/max as lo/hi
    vector<int> neg = {-3, 5, 0, -3, 2, -1};
    for (int x : counting_sort(neg, [](int v) { return v; }, -3, 5)) cout << x << ' ';
    cout << "\n";

    // --- records sorted by a key, stability visible (Ann before Cy, Bo before Di)
    vector<Student> s = {{"Ann", 90}, {"Bo", 70}, {"Cy", 90}, {"Di", 70}, {"Ed", 80}};
    for (auto &st : counting_sort(s, [](const Student &x) { return x.grade; }, 0, 100))
        cout << st.name << ':' << st.grade << ' ';
    cout << "\n";

    // --- descending
    for (auto &st : counting_sort(s, [](const Student &x) { return x.grade; }, 0, 100, true))
        cout << st.name << ':' << st.grade << ' ';
    cout << "\n";

    // --- characters (the key range is tiny: 256), sorting a string
    string word = "counting sort";
    string sorted_word;
    for (char c : counting_sort(vector<char>(word.begin(), word.end()),
                                [](char c) { return static_cast<unsigned char>(c); }, 0, 255))
        sorted_word += c;
    cout << '"' << sorted_word << "\"\n";
    return 0;
}
