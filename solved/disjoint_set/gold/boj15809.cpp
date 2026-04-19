#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> par, sz, ans;

int find_(int a) {
    if (par[a] == a) return a;
    return par[a] = find_(par[a]);
}

int union_(int a, int b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
    sz[b] = 0;
    return 0;
}

int union_2(int a, int b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    if (sz[a] == sz[b]) sz[a] = sz[b] = 0;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] -= sz[b];
    sz[b] = 0;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b, c; cin >> n >> m;
    par.resize(n + 1);
    sz.resize(n + 1);
    for (i = 1; i <= n; i++) {
        cin >> sz[i];
        par[i] = i;
    }
    for (i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (a == 1) union_(b, c);
        else union_2(b, c);
    }
    for (i = 1; i <= n; i++) {
        if (i == find_(i) && sz[i] > 0) ans.emplace_back(sz[i]);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto& iter : ans) cout << iter << ' ';
}
