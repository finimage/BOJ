#include<bits/stdc++.h>
using namespace std;

int a, b, n, cnt;
vector<bool> visited;
vector<vector<int>> g;
vector<unordered_set<int>> us;
vector<int> degree;

void dfs(int ind) {
    cout << ind << ' ';
    for (int i = 0; i < g[ind].size(); i++) {
        if (us[ind].count(g[ind][i])) continue;
        us[ind].insert(g[ind][i]);
        us[g[ind][i]].insert(ind);
        dfs(g[ind][i]);
    }
}

void dfs_(int ind) {
    cnt++;
    visited[ind] = 1;
    for (auto& iter : g[ind]) {
        if (visited[iter]) continue;
        dfs_(iter);
    }
}

bool connected() {
    visited.resize(n + 1);
    dfs_(1);
    return cnt != n;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, ans = 1; cin >> a >> b >> n;
    us.resize(n + 1);
    g.resize(n + 1);
    degree.resize(n + 1);
    for (i = 1; i <= n; i++) {
        if (i - a >= 1) {
            g[i].push_back(i - a);
            g[i - a].push_back(i);
            ans++;
            degree[i]++;
            degree[i - a]++;
        }
        if (a != b && i - b >= 1) {
            g[i].push_back(i - b);
            g[i - b].push_back(i);
            ans++;
            degree[i]++;
            degree[i - b]++;
        }
    }
    if (connected()) {
        cout << -1;
        return 0;
    }
    int cnt = 0, odd[2] = {0,};
    for (i = 1; i <= n; i++) {
        if (degree[i] % 2) {
            if (cnt == 2) {
                cout << -1;
                return 0;
            }
            odd[cnt++] = i;
        }
    }
    cout << ans << '\n';
    if (cnt) dfs(odd[0]);
    else dfs(1);
}   
