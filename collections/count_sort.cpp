
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

vector<int> horspool(const string& text, const string& pattern) {
    vector<int> positions;

    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());

    // An empty pattern is handled separately.
    if (m == 0) {
        throw invalid_argument("Pattern must not be empty.");
    }

    if (m > n) {
        return positions;
    }

    // Step 1: Build the shift table.
    vector<int> shift(256, m);

    for (int i = 0; i < m - 1; ++i) {
        shift[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }

    // Step 2: Search the text.
    int alignment = m - 1;

    while (alignment < n) {
        int j = m - 1;

        // Compare pattern and text from right to left.
        while (j >= 0 &&
               pattern[j] == text[alignment - (m - 1 - j)]) {
            --j;
        }

        // If every character matches, record the starting index.
        if (j < 0) {
            positions.push_back(alignment - m + 1);
        }

        // Shift based on the text character aligned with
        // the last character of the pattern.
        alignment += shift[
            static_cast<unsigned char>(text[alignment])
        ];
    }

    return positions;
}

int main() {
    string text = "ABAAABCDABCABC";
    string pattern = "ABC";

    try {
        vector<int> matches = horspool(text, pattern);

        if (matches.empty()) {
            cout << "No matches found.\n";
        } else {
            cout << "Pattern found at indices: ";

            for (int position : matches) {
                cout << position << " ";
            }

            cout << "\n";
        }
    } catch (const invalid_argument& error) {
        cerr << error.what() << "\n";
        return 1;
    }

    return 0;
}
