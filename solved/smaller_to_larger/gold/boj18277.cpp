#include<bits/stdc++.h>
using namespace std;

int n, m, q;
vector<set<int>> vs;
vector<int> v;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, j, a, b; cin >> n >> q;
    vs.resize(n + 1);
    v.resize(n + 1);
    for (i = 1; i <= n; i++) {
        v[i] = i;
        cin >> m;
        for (j = 0; j < m; j++) {
            cin >> a;
            vs[i].insert(a);
        }
    }
    while (q--) {
        cin >> j >> a;
        if (j == 1) {
            cin >> b;
            if (vs[v[a]].size() < vs[v[b]].size()) swap(v[a], v[b]);
            for (auto& iter : vs[v[b]]) vs[v[a]].insert(iter);
            vs[v[b]].clear();
        }
        else cout << vs[v[a]].size() << '\n';
    }
}
