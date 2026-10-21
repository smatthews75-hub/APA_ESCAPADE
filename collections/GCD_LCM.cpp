#include <iostream>

using namespace std;

template<typename T>
constexpr T abs_val(T x) {
    return (x < 0) ? -x : x;
}

template<typename T>
constexpr T GCD(T a, T b) {
    a = abs_val(a);
    b = abs_val(b);

    if (a == 0) return b;
    if (b == 0) return a;

    // Find the greatest power of 2 that divides both a and b
    int shift = 0;
    while (((a | b) & 1) == 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }

    // Divide a by 2 until it becomes odd
    while ((a & 1) == 0) {
        a >>= 1;
    }

    // From here on, 'a' is always odd
    do {
        // Remove all factors of 2 in b
        while ((b & 1) == 0) {
            b >>= 1;
        }

        // Now both a and b are odd. Swap if necessary so a <= b
        if (a > b) {
            T temp = a;
            a = b;
            b = temp;
        }

        // Subtract the smaller odd number from the larger.
        // The result is even, which will be divided by 2 in the next loop.
        b -= a;
    } while (b != 0);

    // Restore the common factors of 2
    return a << shift;
}

template<typename T>
constexpr T LCM(T a, T b) {
    if (a == 0 || b == 0) return 0;
    return (abs_val(a) / GCD(a, b)) * abs_val(b);
}

int main(void) {
    int a, b; cin >> a >> b;
    cout << GCD(a, b) << " " << LCM(a, b);
}