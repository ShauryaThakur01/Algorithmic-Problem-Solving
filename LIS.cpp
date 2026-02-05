#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getLIS(vector<int> arr, int idx, vector<vector<int>> memo, vector<int> visited) {
    // Check if we have already calculated the result
    if(visited[idx]) {
        return memo[idx];
    }

    vector<int> longest = {idx};

    for(int prev = 0; prev<idx; prev++) {
        if(arr[prev] < arr[idx]) {
            vector<int> sub = getLIS(arr, prev, memo, visited);

            if(sub.size()+1 > longest.size()) {
                vector<int> currentPath = sub;
                currentPath.push_back(idx);
                longest = currentPath;
            }
        }
    }

    // Storing the traversed result
    memo[idx] = longest;
    visited[idx] = true;

    return longest;
}

void solve() {
    int n;
    if(!(cin >> n) || n==0) return;

    vector<int> v(n);
    for(int i=0; i<n; i++) {
        cin >> v[i];
    }

    vector<vector<int>> memo(n);
    vector<int> visited(n,false);

    vector<int> bestIndices;

    for(int i=0; i<n; i++) {
        vector<int> current = getLIS(v,i, memo, visited);
        if(current.size() > bestIndices.size()) {
            bestIndices = current;
        }
    }

    cout << bestIndices.size() << "\n";
    for(int x : bestIndices) cout << x << " ";
    cout << "\n";


}

int main()
{
    solve();
    return 0;
}
