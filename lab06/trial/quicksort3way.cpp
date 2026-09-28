#include <bits/stdc++.h>
using namespace std;

#define ll long long

/*
    3-way QuickSort partitioning.

    We maintain this structure inside A[l..r]:

    [ < pivot ][ = pivot ][ unknown ][ > pivot ]
    ^         ^          ^          ^          ^
    l        lt          i         gt          r

    More precisely:

        A[l .. lt-1]  < pivot
        A[lt .. i-1]  = pivot
        A[i  ... gt]   unknown
        A[gt+1 .. r]  > pivot

    The pivot value is A[l].
*/

// Returns {lt, gt}.
// After partition:
//     A[l .. lt-1] < pivot
//     A[lt ... gt]  = pivot
//     A[gt+1 .. r] > pivot
pair<int, int> partition3Way(vector<int>& A, int l, int r)
{
    int pivot = A[l];
    int lt = l;// lt = beginning of the "equal pivot" region
    int i  = l + 1;// i  = first unknown element
    int gt = r;// gt = end of the unknown region

    while (i <= gt) {
        if (A[i] < pivot) {
            swap(A[lt++], A[i++]); // Increment AFTER accessing
        }
        else if (A[i] > pivot)
        {
            /*
                Current element belongs on the RIGHT.

                Swap it with A[gt].

                Before:

                [ < ][ = ][ X ][ > ]
                            i    gt

                After the swap, the element coming from A[gt]
                is UNKNOWN.

                Therefore:

                    gt moves left
                    BUT i does NOT move

                because we still need to inspect the new A[i].

                This is very important.

                Example:

                    A[i] = 9   (> pivot)
                    A[gt] = 2  (< pivot)

                After swapping:

                    A[i] = 2

                We must process that 2 next.
            */

            swap(A[i], A[gt--]); // Decrement AFTER accessing

            // IMPORTANT:
            // Do NOT increment i here.
        }
        else
        {
            /*
                A[i] == pivot

                It already belongs in the middle.

                So simply move i forward.

                [ < ][ = ][ X ][ > ]
                           ^
                           i

                becomes

                [ < ][ = ][ X ][ > ]
                              ^
                              i
            */

            i++;
        }
    }

    /*
        Loop finished because:

            i > gt

        Therefore there are no unknown elements left.

        Final structure:

        [ < pivot ][ = pivot ][ > pivot ]
          l..lt-1    lt..gt     gt+1..r
    */

    return {lt, gt};
}


/*
    QuickSort using the 3-way partition above.

    We only recursively sort:

        A[l .. lt-1]
        A[gt+1 .. r]

    We DO NOT sort A[lt .. gt]
    because every element there is already equal to pivot.
*/
void quickSort(vector<int>& A, int l, int r)
{
    // Base case:
    // 0 or 1 element is already sorted.
    if (l >= r) return;

    auto [lt, gt] = partition3Way(A, l, r);

    /*
        After partition:

        [ < pivot ][ = pivot ][ > pivot ]
          l..lt-1    lt..gt     gt+1..r

        So recursively sort only the left and right.
    */

    quickSort(A, l, lt - 1);
    quickSort(A, gt + 1, r);
}

void solve() {
    int n_; cin >> n_;
    vector<int> A_(n_);
    for (auto &x_ : A_) cin >> x_;
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