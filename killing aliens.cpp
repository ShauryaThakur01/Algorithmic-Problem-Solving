#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int x, y;
char maze[55][55];
int dists[105][105];
int node_idx[55][55];
int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

struct Node {
    int r;
    int c;
    int d;
};


// bfs
void bfs(int start_r, int start_c, int u, int num_nodes) {
    int d[55][55];
    for(int i=0; i<y; i++) for(int j=0; j<x; j++) d[i][j] = -1;
    
    queue<Node> q;
    q.push({start_r, start_c, 0});
    d[start_r][start_c] = 0;

    while(!q.empty()){
        Node curr = q.front(); q.pop();
        if(node_idx[curr.r][curr.c] != -1){
            dists[u][node_idx[curr.r][curr.c]] = curr.d;
        }
        for(int i=0; i<4; i++){
            int nr = curr.r + dx[i], nc = curr.c + dy[i];
            if(nr >= 0 && nr < y && nc >= 0 && nc < x && maze[nr][nc] != '#' && d[nr][nc] == -1){
                d[nr][nc] = curr.d + 1;
                q.push({nr, nc, curr.d + 1});
            }
        }
    }
}






//prim
int prim(int n) {
    vector<int> min_d(n, 1e9);
    vector<bool> visited(n, false);
    min_d[0] = 0;
    int total_cost = 0;
    for(int i=0; i<n; i++){
        int u = -1;
        for(int v=0; v<n; v++) if(!visited[v] && (u == -1 || min_d[v] < min_d[u])) u = v;
        visited[u] = true;
        total_cost += min_d[u];
        for(int v=0; v<n; v++) if(!visited[v]) min_d[v] = min(min_d[v], dists[u][v]);
    }
    return total_cost;
}







int main() {
    int N;
    cin >> N;

    while(N--) {
        cin >> x >> y;
        string dummy;
        getline(cin, dummy);
        vector<pair<int,int>> nodes;

        for(int i=0; i<y; i++) {
            string line; 
            getline(cin, line);
            for(int j=0; j<x; j++) {
                maze[i][j] = line[j];
                node_idx[i][j] = -1;

                if(maze[i][j] == 'S' || maze[i][j] == 'A') {
                    node_idx[i][j] = nodes.size();
                    nodes.push_back({i,j});
                }
            }
        }
        for(int i=0; i<nodes.size(); i++) {
            bfs(nodes[i].first, nodes[i].second, i, nodes.size());
        }

        cout << prim(nodes.size()) << "\n";
    }

    return 0;
}

