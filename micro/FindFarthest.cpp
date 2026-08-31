#include <algorithm>
#include <iostream>
#include <cstddef>
#include <vector>
#include <random>

using namespace std;

struct RESULT {
    int min_;
    int max_;
    
};

RESULT FindFarthest(vector<int> A) {
    size_t len_ = A.size();
    int min_ = A[0];
    int max_ = A[0];
    for (size_t i = 0; i < len_; i++) {
        if (A[i] > max_) {max_ = A[i];}
        if (A[i] < min_) {min_ = A[i];}
    }
    return {min_, max_};
}

int main() {
    std::random_device rd;     
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> randint(0, 100); // For a 1-6 dice roll

    int n_; cin >> n_;
    vector<int> A(n_, 0);
    for (int i = 0; i < n_; i++) {
        A[i] = randint(gen);
        cout  << A[i] << " ";
    }
    cout << endl;


    RESULT res = FindFarthest(A);
    sort(A.begin(), A.end());
    for (int i = 0; i < n_; i++) {cout  << A[i] << " ";}
    cout << endl;
    cout << res.min_ << " " << res.max_ << endl;
}