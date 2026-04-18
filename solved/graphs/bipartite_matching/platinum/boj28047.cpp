#include<bits/stdc++.h>
using namespace std;

string s;
unordered_map<string, int> um;
unordered_map<int, string> mu;
vector<vector<int>> g;
int n, m, grid[302][302], check[301], ans[301];
bool visited[301];

int dfs(int ind) {
    for (auto& iter : g[ind]) {
        if (visited[iter]) continue;
        visited[iter] = 1;
        if (!check[iter]) return check[iter] = ind;
        else if (dfs(check[iter])) return check[iter] = ind;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, a, b; cin >> n;
    g.resize(n + 1);
    for (i = 1; i <= n; i++) {
        cin >> s;
        um[s] = i;
        mu[i] = s;
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) grid[i][j] = 1;
        grid[i][301] = 1;
        grid[301][i] = 1;
    }
    cin >> m;
    for (i = 0; i < m; i++) {
        cin >> a >> b;
        for (j = 0; j < a; j++) {
            cin >> s;
            grid[b][um[s]]++;
            grid[b][301] = max(grid[b][301], grid[b][um[s]]);
            grid[301][um[s]] = max(grid[301][um[s]], b);
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (grid[i][j] == grid[i][301] && i >= grid[301][j]) g[i].push_back(j);
        }
    }
    for (i = 1; i <= n; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i);
    }
    for (i = 1; i <= n; i++) ans[check[i]] = i;
    for (i = 1; i <= n; i++) cout << mu[ans[i]] << ' ';
}
