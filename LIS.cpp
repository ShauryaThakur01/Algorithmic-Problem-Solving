#include <iostream>
#include <vector>

using namespace std;

// Returns the LIS ending at index 'idx'
vector<int> getLIS(vector<int> const& arr, int idx) {
    // Base case: The LIS ending at idx with no previous elements is just arr[idx]
    vector<int> longest = {arr[idx]};

    for (int prev = 0; prev < idx; prev++) {
        if (arr[prev] < arr[idx]) {
            vector<int> sub = getLIS(arr, prev);
            // If this path (+ current element) is longer than our current best
            if (sub.size() + 1 > longest.size()) {
                sub.push_back(arr[idx]);
                longest = sub;
            }
        }
    }
    return longest;
}

void solve() {
    int n;
    if (!(cin >> n) || n == 0) return;

    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    vector<int> overallBest;

    // Check LIS ending at every possible index
    for (int i = 0; i < n; i++) {
        vector<int> current = getLIS(v, i);
        if (current.size() > overallBest.size()) {
            overallBest = current;
        }
    }

    cout << "Length: " << overallBest.size() << "\nElements: ";
    for (int x : overallBest) cout << x << " ";
    cout << endl;
}

int main() {
    solve();
    return 0;
}
