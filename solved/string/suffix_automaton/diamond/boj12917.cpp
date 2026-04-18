#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 998244353
using namespace std;

struct Node {
    int len, slink, cnt;
    map<char, int> edge;
};

Node g[200001];
int sz, last;
string s;

bool cmp(int a, int b) {
    return g[a].len > g[b].len;
}

void upt(char c) {
    int tmp = sz++;
    g[tmp].len = g[last].len + 1;
    g[tmp].cnt = 1;
    int p = last;
    while (p != -1 && !g[p].edge.count(c)) {
        g[p].edge[c] = tmp;
        p = g[p].slink;
    }
    if (p == -1) g[tmp].slink = 0;
    else {
        int q = g[p].edge[c];
        if (g[q].len == g[p].len + 1) g[tmp].slink = q;
        else {
            int cl = sz++;
            g[cl].len = g[p].len + 1;
            g[cl].slink = g[q].slink;
            g[cl].edge = g[q].edge;
            while (p != -1 && g[p].edge[c] == q) {
                g[p].edge[c] = cl;
                p = g[p].slink;
            }
            g[q].slink = g[tmp].slink = cl;
        }
    }
    last = tmp;
}

void solve() {
    int i; cin >> s;
    g[0].len = 0;
    g[0].slink = -1;
    sz = 1;
    last = 0;
    for (auto& iter : s) upt(iter);
    vector<int> v(sz - 1);
    for (i = 1; i < sz; i++) v[i - 1] = i;
    sort(v.begin(), v.end(), cmp);
    for (i = 1; i < sz; i++) g[g[v[i - 1]].slink].cnt += g[v[i - 1]].cnt;
    ll ans = 0;
    for (i = 1; i < sz; i++) ans = max(ans, (ll)g[i].len * g[i].cnt);
    cout << ans;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
