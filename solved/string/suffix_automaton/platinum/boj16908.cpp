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

Node g[2000021];
int n, sz, last, ans;
string s, tmps;
bool visited[2000021];
int ck[2000021], ckck;

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

void dfs() {
    stack<int> st;
    st.push(0);
    while (!st.empty()) {
        int k = st.top(), tf = 0;
        st.pop();
        if (visited[k]) continue;
        for (auto& iter : g[k].edge) {
            if (!visited[iter.y]) tf = 1;
            if (tf) break;
        }
        if (tf) {
            st.push(k);
            for (auto& iter : g[k].edge) {
                if (!visited[iter.y]) st.push(iter.y);
            }
        }
        else {
            for (auto& iter : g[k].edge) {
                if ('0' <= iter.x && iter.x <= '9') ck[k] |= 1 << (iter.x - '0');
                else ck[k] |= ck[iter.y];
            }
            visited[k] = 1;
            if (ck[k] == ckck) ans = max(ans, g[k].len);
        }
    }
}

void solve() {
    int i = 0; cin >> n;
    for (i = 0; i < n; i++) {
        cin >> tmps;
        s += tmps + char(i + '0');
        ckck |= 1 << i;
    }
    g[0].len = 0;
    g[0].slink = -1;
    sz++;
    for (auto& iter : s) upt(iter, i++);
    dfs();
    cout << ans;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
