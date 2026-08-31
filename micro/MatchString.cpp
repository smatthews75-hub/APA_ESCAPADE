#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> MatchString(string &original, string &match) {
    vector<int> match_indeces; match_indeces.reserve(match.size());
    size_t ori_len = original.size();
    size_t match_len = match.size();
    for (size_t i = 0; i < ori_len; i++) {
        if (original[i] == match[match_indeces.size()]) {match_indeces.emplace_back(i);}
        else if (match_indeces.size() != 0) {match_indeces.clear();}
        if (match_indeces.size() == match_len) {break;}
    }
    return match_indeces;
}

void print_match(string &original, vector<int> &match_indeces) {
    for (int &i : match_indeces) {
        cout << original[i];
    }
    cout << endl;
}

int main() {
    string original = "Pak Sanga has a rather odd teaching style but at least he is passionate about it.";
    string match = "t at";
    vector<int> match_indeces;
    match_indeces = MatchString(original, match);
    print_match(original, match_indeces);

    getline(cin, original);
    getline(cin, match);
    match_indeces = MatchString(original, match);
    print_match(original, match_indeces);
}