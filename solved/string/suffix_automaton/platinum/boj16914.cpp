#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 998244353
using namespace std;

/*
suffix automaton 구현 연습
https://cp-algorithms.com/string/suffix-automaton.html
참고
*/

struct Node {
    int len, slink;
    map<char, int> edge;
};

Node g[180001];
int sz, last, qq, k;
string s;
ll dp[200001];

void upt(char c) {
    int tmp = sz++;
    g[tmp].len = g[last].len + 1;
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

ll make_dp(int ind) {
    if (dp[ind] != -1) return dp[ind];
    ll cnt = 1;
    for (auto& iter : g[ind].edge) cnt += make_dp(iter.y);
    return dp[ind] = cnt;
}

void print(int ind, int cnt) {
    for (auto& iter : g[ind].edge) {
        if (cnt > dp[iter.y]) cnt -= dp[iter.y];
        else {
            cout << iter.x;
            if (cnt > 1) print(iter.y, cnt - 1);
            break;
        }
    }
}

void solve() {
    int i; cin >> s >> qq;
    g[0].len = 0;
    g[0].slink = -1;
    sz = 1;
    for (auto& iter : s) upt(iter);
    for (i = 0; i < sz; i++) dp[i] = -1;
    make_dp(0);
    while (qq--) {
        cin >> k;
        if (k >= dp[0]) cout <<"-1\n";
        else {
            print(0, k);
            cout << '\n';
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
