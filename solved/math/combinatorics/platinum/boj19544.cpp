#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

int n;
vector<int> p, pp, cy, v;
vector<vector<int>> g;

int parent1(int a) {
    if (a == p[a]) return a;
    return p[a] = parent1(p[a]);
}

bool union1(int a, int b) {
    a = parent1(a);
    b = parent1(b);
    if (a == b) return 1;
    if (a < b) swap(a, b);
    p[a] = b;
    return 0;
}

bool cmp(int a, int b) {
    return g[a].size() < g[b].size();
}

ll fac(ll a) {
    ll res = 1;
    for (ll i = 1; i <= a; i++) res = res * i % MOD;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, a; cin >> n;
    g.resize(n + 1);
    p.resize(n + 1);
    v.resize(n + 1);
    pp.resize(n + 1);
    cy.resize(n + 1);
    for (i = 1; i <= n; i++) v[i] = p[i] = pp[i] = i;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cin >> a;
            if (a == 1) {
                union1(i, j);
                g[i].push_back(j);
            }
        }
    }
    vector<ll> ans(n + 1, 1);
    sort(v.begin() + 1, v.end(), cmp);
    for (i = 1; i <= n; i++) {
        int cnt = 1, cycnt = 0, cycle = 0;
        for (auto& iter : g[v[i]]) {
            if (iter == v[i]) {
                continue;
            }
            if (cy[iter]) {
                cycnt++;
                cycle = iter;
            }
            else cnt++;
        }
        if (cy[v[i]]) continue;
        if (cnt == g[v[i]].size()) {
            for (auto& iter : g[v[i]]) cy[iter] = 1;
            ans[p[v[i]]] = fac(cnt - 1);
        }
        else {
            if (cnt == 1) ans[p[cycle]] = ans[p[cycle]] * cycnt % MOD;
        }
    }
    ll res = 1;
    for (i = 1; i <= n; i++) res = res * ans[i] % MOD;
    cout << res;
}
