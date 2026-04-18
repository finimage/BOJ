#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, ll>
#define x first
#define y second
using namespace std;

int n; ll cnt;
vector<vector<pii>> g;

void dfs(int ind, int pre, ll c) {
    ll Max = 0, total = 0;
    for (auto& iter : g[ind]) {
        if (iter.x == pre) continue;
        dfs(iter.x, ind, iter.y);
        total += iter.y;
        Max= max(Max, iter.y);
    }
    if (Max - c > total - Max) cnt += Max - c;
    else if (c <= total) {
        total -= c;
        cnt += (total + 1) / 2;
    }
}

void solve() {
    int i, a, b, c; cin >> n;
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    dfs(1, 0, 0);
    cout << cnt << '\n';
    cnt = 0;
    g.clear();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
