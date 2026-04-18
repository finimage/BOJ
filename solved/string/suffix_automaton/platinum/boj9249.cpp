#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct Node {
    int len, slink, ind;
    map<char, int> edge;
};

Node g[400004];
int sz, last, ans, ansind;
string s, s1, s2;
bool cka[400004], ckb[400004], visited[400004];

void upt(char c, int ind) {
    int tmp = sz++;
    g[tmp].len = g[last].len + 1;
    g[tmp].ind = ind;
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
            g[cl].ind = g[q].ind;
            while (p != -1 && g[p].edge[c] == q) {
                g[p].edge[c] = cl;
                p = g[p].slink;
            }
            g[q].slink = g[tmp].slink = cl;
        }
    }
    last = tmp;
}

void dfs(int ind) {
    visited[ind] = 1;
    for (auto& iter : g[ind].edge) {
        if (!visited[iter.y]) dfs(iter.y);
        if (iter.x == 'A') cka[ind] = 1;
        else if (iter.x == 'B') ckb[ind] = 1;
        else {
            if (cka[iter.y]) cka[ind] = 1;
            if (ckb[iter.y]) ckb[ind] = 1;
        }
    }
    if (cka[ind] && ckb[ind]) {
        if (ans < g[ind].len) {
            ans = g[ind].len;
            ansind = g[ind].ind;
        }
    }
}

void solve() {
    int i = 0; cin >> s1 >> s2;
    s = s1 + "A" + s2 + "B";
    g[0].len = 0;
    g[0].slink = -1;
    sz++;
    for (auto& iter : s) upt(iter, i++);
    dfs(0);
    cout << ans << '\n';
    for (i = ansind - ans + 1; i <= ansind; i++) cout << s[i];
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
