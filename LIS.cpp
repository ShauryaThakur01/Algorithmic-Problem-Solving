#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getLIS(vector<int> arr, int idx) {
    vector<int> longest = {idx};

    for(int prev = 0; prev<idx; prev++) {
        if(arr[prev] < arr[idx]) {
            vector<int> sub = getLIS(arr, prev);

            if(sub.size()+1 > longest.size()) {
                sub.push_back(idx);
                longest = sub;
            }
        }
    }

    return longest;
}

void solve() {
    int n;
    if(!(cin >> n) || n==0) return;

    vector<int> v(n);
    for(int i=0; i<n; i++) {
        cin >> v[i];
    }

    vector<int> overallBest;

    for(int i=0; i<n; i++) {
        vector<int> current = getLIS(v,i);
        if(current.size() > overallBest.size()) {
            overallBest = current;
        }
    }

    cout << overallBest.size() << "\n";
    for(int x : overallBest) cout << x << " ";
    cout << "\n";


}

int main()
{
    solve();
    return 0;
}
