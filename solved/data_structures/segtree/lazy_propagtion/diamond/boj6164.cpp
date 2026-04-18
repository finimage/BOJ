#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct info {
    int le, ri, leind, riind, Max, Sum;
};

info tree[200004];
int n, m, ans, lazy[200004];

info init(int start, int end, int ind) {
    if (start == end) return tree[ind] = {1,1,end,end,1,1};
    int mid = (start + end) / 2;
    info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = {l.le+r.le,l.le+r.le,end,start,l.le+r.le,l.le+r.le};
}

void lazy_pro(int start, int end, int ind) {
    if (!lazy[ind]) return;
    int k = lazy[ind];
    lazy[ind] = 0;
    if (k == 1) tree[ind] = {0,0,0,0,0,end-start+1};
    else tree[ind] = {end-start+1,end-start+1,end,start,end-start+1,end-start+1};
    if (start == end) return;
    lazy[ind * 2] = lazy[ind * 2 + 1] = k;
}

info update(int start, int end, int ind, int le, int ri, int v) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        lazy[ind] = v;
        lazy_pro(start, end, ind);
        return tree[ind];
    }
    int mid = (start + end) / 2;
    info l = update(start, mid, ind * 2, le, ri, v), r = update(mid + 1, end, ind * 2 + 1, le, ri, v);
    info tmp;
    tmp.le = l.le;
    tmp.leind = l.leind;
    if (l.le == l.Sum && r.le > 0) {
        tmp.le = l.le + r.le;
        tmp.leind = r.leind;
    }
    tmp.ri = r.ri;
    tmp.riind = r.riind;
    if (r.ri == r.Sum && l.ri > 0) {
        tmp.ri = l.ri + r.ri;
        tmp.riind = l.riind;
    }
    tmp.Sum = l.Sum + r.Sum;
    tmp.Max = max(max(l.Max, r.Max), l.ri + r.le);
    return tree[ind] = tmp;
}

int res(int start, int end, int ind, int v) {
    lazy_pro(start, end, ind);
    if (tree[ind].Max < v) {
        ans++;
        return 0;
    }
    if (tree[ind].le >= v) {
        update(1, n, 1, start, start + v - 1, 1);
        return start;
    }
    int mid = (start + end) / 2;
    lazy_pro(start, mid, ind * 2);
    lazy_pro(mid + 1, end, ind * 2 + 1);
    if (tree[ind * 2].Max >= v) return res(start, mid, ind * 2, v);
    if (tree[ind * 2].ri + tree[ind * 2 + 1].le >= v) {
        int L = tree[ind * 2].ri, R = v - tree[ind * 2].ri, resind = tree[ind * 2].riind;
        if (L > 0) update(1, n, 1, tree[ind * 2].riind, mid, 1);
        else resind = mid + 1;
        update(1, n, 1, mid + 1, mid + R, 1);
        return resind;
    }
    return res(mid + 1, end, ind * 2 + 1, v);
}

void solve() {
    int i, a, b, c; cin >> n >> m;
    init(1, n, 1);
    while (m--) {
        cin >> c >> a;
        if (c == 1) cout << res(1, n, 1, a) << '\n';
        else {
            cin >> b;
            update(1, n, 1, a, a + b - 1, -1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
