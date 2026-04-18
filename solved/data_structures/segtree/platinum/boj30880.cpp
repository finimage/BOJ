#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

struct Info {
    ll R, RO, ROC, ROCK;
    ll o, c, k, oc, ck, ock;
    ll pow2len;
};

int n, q;
string s;
Info tree[1000000], info0;

Info merge(Info l, Info r) {
    Info ret;
    ret.o = (l.o + r.o) % MOD;
    ret.c = (l.c + r.c) % MOD;
    ret.k = (l.k + r.k) % MOD;
    ret.oc = (l.oc + r.oc + l.o * r.c) % MOD;
    ret.ck = (l.ck + r.ck + l.c * r.k) % MOD;
    ret.ock = (l.ock + r.ock + l.o * r.ck + l.oc * r.k) % MOD;
    ret.R = (l.R + l.pow2len * r.R) % MOD;
    ret.RO = (l.RO + l.pow2len * r.RO + l.R * r.o) % MOD;
    ret.ROC = (l.ROC + l.pow2len * r.ROC + l.R * r.oc + l.RO * r.c) % MOD;
    ret.ROCK = (l.ROCK + l.pow2len * r.ROCK + l.R * r.ock + l.RO * r.ck + l.ROC * r.k) % MOD;
    ret.pow2len = l.pow2len * r.pow2len % MOD;
    return ret;
}

Info update(int start, int end, int ind, int i, char c) {
    if (i < start || end < i) return tree[ind];
    if (start == end) {
        tree[ind] = info0;
        if (c == 'R') tree[ind].R = 1;
        if (c == 'O') tree[ind].o = 1;
        if (c == 'C') tree[ind].c = 1;
        if (c == 'K') tree[ind].k = 1;
        tree[ind].pow2len = 2;
        return tree[ind];
    }
    int mid = (start + end) / 2;
    Info l = update(start, mid, ind * 2, i, c), r = update(mid + 1, end, ind * 2 + 1, i, c);
    return tree[ind] = merge(l, r);
}

Info query(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return info0;
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    Info l = query(start, mid, ind * 2, le, ri), r = query(mid + 1, end, ind * 2 + 1, le, ri);
    Info ret = merge(l, r);
    return ret;
}

void solve() {
    int i, a, b, c; char C; cin >> n >> s >> q;
    for (i = 0; i < n; i++) update(1, n, 1, i + 1, s[i]);
    info0.pow2len = 1;
    while (q--) {
        cin >> a >> b;
        if (a == 1) {
            cin >> C;
            update(1, n, 1, b, C);
        }
        else {
            cin >> c;
            cout << query(1, n, 1, b, c).ROCK << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
