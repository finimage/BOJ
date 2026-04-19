#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

ll n, m, k, s, t;
ll dismax[15][100001];
vector<vector<pll>> g;
bool visited[100001][15];

void dfs(int ind, int kcnt) {
    visited[ind][kcnt] = 1;
    ll tmpt = -1;
    if (t == ind) {
        tmpt = 0;
    }
    for (auto& iter : g[ind]) {
        if (iter.y == 0) {
            if (kcnt < k && !visited[iter.x][kcnt + 1]) {
                dfs(iter.x, kcnt + 1);
                if (dismax[kcnt + 1][iter.x] != -1) tmpt = max(tmpt, dismax[kcnt + 1][iter.x]);
            }
            else if (kcnt < k && visited[iter.x][kcnt + 1]) {
                if (dismax[kcnt + 1][iter.x] != -1) tmpt = max(tmpt, dismax[kcnt + 1][iter.x]);
            }
        }
        else {
            if (!visited[iter.x][kcnt]) {
                dfs(iter.x, kcnt);
                if (dismax[kcnt][iter.x] != -1) tmpt = max(tmpt, iter.y + dismax[kcnt][iter.x]);
            }
            else {
                if (dismax[kcnt][iter.x] != -1) tmpt = max(tmpt, iter.y + dismax[kcnt][iter.x]);
            }
        }
    }
    dismax[kcnt][ind] = tmpt;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll i, a, b, c; cin >> n >> m >> k >> s >> t;
    for (i = 0; i <= k; i++) {
        for (int j = 1; j <= n; j++) dismax[i][j] = -1;
    }
    g.resize(n + 1);
    for (i = 0; i < m; i++) {
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        g[b].push_back({a,0});
    }
    for (i = 1; i <= n; i++) {
        for (int j = k; j >= 0; j--) {
            if (!visited[i][j]) dfs(i, j);
        }
    }
    ll ans = -1;
    for (i = 0; i <= k; i++) ans = max(ans, dismax[i][s]);
    cout << ans;
}
