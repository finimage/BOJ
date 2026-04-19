#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, tf, end_, ans;
vector<vector<int>> g;
vector<int> path;

void dfs(int ind, int pre) {
    path.emplace_back(ind);
    if (ind == end_) {
        tf = 1;
        return;
    }
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs(iter, ind);
        if (tf) return;
    }
    path.pop_back();
}

void dfs2(int ind, int pre) {
    ans++;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs2(iter, ind);
    }
}

void solve() {
    int i, a, b, c; cin >> n;
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cin >> a >> b >> c;
    if (a == b) {
        cout << n;
        return;
    }
    end_ = b;
    dfs(a, a);
    int tmp = 0;
    for (i = 0; i < path.size(); i++) {
        if (path[i] == c) {
            tmp = i;
            break;
        }
    }
    if (path[tmp] == a) {
        for (auto& iter : g[a]) {
            if (iter == path[1]) {
                iter = a;
                break;
            }
        }
        dfs2(a, a);
        cout << ans;
    }
    else if (path[tmp] == b) {
        for (auto& iter : g[b]) {
            if (iter == path[(int)path.size() - 2]) {
                iter = b;
                break;
            }
        }
        dfs2(b, b);
        cout << ans;
    }
    else {
        for (auto& iter : g[path[tmp]]) {
            if (iter == path[tmp + 1] || iter == path[tmp - 1]) {
                iter = path[tmp];
            }
        }
        dfs2(path[tmp], path[tmp]);
        cout << ans;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
