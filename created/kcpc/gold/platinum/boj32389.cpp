#include<bits/stdc++.h>
using namespace std;

int n, m, k;
vector<vector<int>> g, dp;
vector<int> check;

void dfs(int ind, int pre) {
    vector<int> tmp(k + 1, 0);
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs(iter, ind);
        int i, j;
        vector<int> tmp_(k + 1, 0);
        for (i = 0; i <= k; i++) {
            for (j = 0; j <= k - i; j++) {
                tmp_[i + j] = max(tmp_[i + j], tmp[i] + dp[iter][j]);
            }
        }
        tmp = tmp_;
    }
    if (check[ind]) {
        for (int i = k; i > 0; i--) tmp[i] = tmp[i - 1] + 1;
        tmp[0] = 0;
    }
    else {
        for (int i = 0; i <= k; i++) tmp[i]++;
    }
    dp[ind] = tmp;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> n >> m >> k;
    g.resize(n + 1);
    dp.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    check.resize(n + 1);
    for (i = 0; i < m; i++) {
        cin >> a;
        check[a] = 1;
    }
    dfs(1, 0);
    int ans = 0;
    for (i = 0; i <= k; i++) ans = max(ans, dp[1][k]);
    cout << ans;
}
