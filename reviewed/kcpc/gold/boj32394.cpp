#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll ans;
int n, m;
vector<set<int>> g;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, t, a, b; cin >> n >> m;
    g.resize(n + 1);
    for (i = 0; i < m; i++) {
        cin >> a >> b;
        g[a].insert(b);
        g[b].insert(a);
    }
    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            ll cnt = 0;
            for (auto& iter : g[i]) {
                if (g[j].count(iter)) cnt++;
            }
            ans += cnt * (cnt - 1) / 2;
        }
    }
    cout << ans / 2 % 1000000007;
}
