#include<bits/stdc++.h>
using namespace std;

int n;
bool visited[100001];
vector<int> dis;
vector<vector<int>> g;
queue<int> q;

int bfs(int start, int k) {
    int a, res = start;
    q.push(start);
    visited[start] = 1;
    if (k) dis[start] = 1;
    while (!q.empty()) {
        res = a = q.front();
        q.pop();
        for (auto& iter : g[a]) {
            if (visited[iter]) continue;
            visited[iter] = 1;
            if (k) dis[iter] = dis[a] + 1;
            q.push(iter);
        }
    }
    memset(visited, 0, sizeof(visited));
    return res;
}

void solve() {
    int i, a, b; cin >> n;
    g.resize(n + 1);
    dis.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        a++;
        b++;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cout << dis[bfs(bfs(1, 0), 1)] / 2 << '\n';
    g.clear();
    dis.clear();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
