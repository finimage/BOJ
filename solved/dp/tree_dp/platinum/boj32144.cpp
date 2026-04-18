#include<bits/stdc++.h>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n, ans[300001];
pii dp[300001][3];
vector<int> g[300001];

void dfs(int ind) {
    for (auto& iter : g[ind]) {
        dfs(iter);
        dp[ind][2].x = max(dp[ind][2].x, dp[iter][2].x);
        if (dp[ind][0].x < dp[iter][0].x + 1) {
            dp[ind][1] = dp[ind][0];
            dp[ind][0] = {dp[iter][0].x + 1, iter};
        }
        else if (dp[ind][1].x < dp[iter][0].x + 1) dp[ind][1] = {dp[iter][0].x + 1, iter};
    }
    dp[ind][2].x = max(dp[ind][2].x, dp[ind][0].x + dp[ind][1].x);
}

void dfs_(int ind, int v, int r) {
    ans[ind] = max(dp[ind][2].x + v, r);
    for (auto& iter : g[ind]) dfs_(iter, max(v, dp[ind][iter == dp[ind][0].y].x) + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, a; cin >> n;
    for (i = 2; i <= n; i++) {
        cin >> a;
        g[a].emplace_back(i);
    }
    dfs(1);
    dfs_(1, 0, dp[1][2].x);
    for (i = 2; i <= n; i++) cout << ans[i] << '\n';
}
