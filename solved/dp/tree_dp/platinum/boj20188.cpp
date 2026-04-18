#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll ans;
int n, cnt[300001];
vector<vector<int>> g;

void dfs(int ind, int pre) {
    cnt[ind] = 1;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs(iter, ind);
        cnt[ind] += cnt[iter];
    }
    if (ind == 1) return;
    ans += (ll)cnt[ind] * (n - cnt[ind]);
    ans += (ll)cnt[ind] * (cnt[ind] - 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> n;
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 0);
    cout << ans;
}
