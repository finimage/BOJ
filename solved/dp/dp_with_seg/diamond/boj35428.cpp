#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define INF 987654321987654321
using namespace std;

struct Info {
    ll v1, v2, mini1, maxi1, mini2, maxi2, val;
};

ll n, m, c;
ll dp[300001];
pll arr[300001];
Info tree[1200004];
pll lazy[1200004];

void init(int start, int end, int ind) {
    tree[ind] = {INF,-2,INF,INF,-2,-2,INF};
    if (start == end) return;
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
}

void lazy_prop(int start, int end, int ind) {
    if (lazy[ind].x) {
        ll k = lazy[ind].x;
        lazy[ind].x = 0;
        tree[ind].v1 = tree[ind].mini1 = tree[ind].maxi1 = k;
        tree[ind].val = tree[ind].maxi2 + k;
        if (start != end) lazy[ind * 2].x = lazy[ind * 2 + 1].x = k;
    }
    if (lazy[ind].y) {
        ll k = lazy[ind].y;
        lazy[ind].y = 0;
        tree[ind].v2 = tree[ind].mini2 = tree[ind].maxi2 = k;
        tree[ind].val = tree[ind].mini1 + k;
        if (start != end) lazy[ind * 2].y = lazy[ind * 2 + 1].y = k;
    }
}

int bs1(int start, int end, int ind, ll t) {
    lazy_prop(start, end, ind);
    if (start == end) {
        if (tree[ind].v1 > t) return -1;
        return end;
    }
    int mid = (start + end) / 2;
    if (tree[ind * 2 + 1].mini1 <= t) return bs1(mid + 1, end, ind * 2 + 1, t);
    return bs1(start, mid, ind * 2, t);
}

Info upt1(int start, int end, int ind, int le, int ri, ll t) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        lazy[ind].x = t;
        lazy_prop(start, end, ind);
        return tree[ind];
    }
    int mid = (start + end) / 2;
    Info l = upt1(start, mid, ind * 2, le, ri, t);
    Info r = upt1(mid + 1, end, ind * 2 + 1, le, ri, t);
    Info tmp = {0,0,l.mini1,r.maxi1,l.mini2,r.maxi2,0};
    if (l.val < r.val) {
        tmp.v1 = l.v1;
        tmp.v2 = l.v2;
        tmp.val = l.val;
    }
    else {
        tmp.v1 = r.v1;
        tmp.v2 = r.v2;
        tmp.val = r.val;
    }
    return tree[ind] = tmp;
}

int bs2(int start, int end, int ind, ll f) {
    lazy_prop(start, end, ind);
    if (start == end) {
        if (tree[ind].v2 > f) return n + 1;
        return end;
    }
    int mid = (start + end) / 2;
    if (tree[ind * 2].maxi2 <= f) return bs2(start, mid, ind * 2, f);
    return bs2(mid + 1, end, ind * 2  +1, f);
}

Info upt2(int start, int end, int ind, int le, int ri, ll f) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        lazy[ind].y = f;
        lazy_prop(start, end, ind);
        return tree[ind];
    }
    int mid = (start + end) / 2;
    Info l = upt2(start, mid, ind * 2, le, ri, f);
    Info r = upt2(mid + 1, end, ind * 2 + 1, le, ri, f);
    Info tmp = {0,0,l.mini1,r.maxi1,l.mini2,r.maxi2,0};
    if (l.val < r.val) {
        tmp.v1 = l.v1;
        tmp.v2 = l.v2;
        tmp.val = l.val;
    }
    else {
        tmp.v1 = r.v1;
        tmp.v2 = r.v2;
        tmp.val = r.val;
    }
    return tree[ind] = tmp;
}

Info upt(int start, int end, int ind, int i, ll dpt, ll f) {
    lazy_prop(start, end, ind);
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = {dpt,2*f-2,dpt,dpt,2*f-2,2*f-2,dpt+2*f-2};
    int mid = (start + end) / 2;
    Info l = upt(start, mid, ind * 2, i, dpt, f);
    Info r = upt(mid + 1, end, ind * 2 + 1, i, dpt, f);
    Info tmp = {0,0,l.mini1,r.maxi1,l.mini2,r.maxi2,0};
    if (l.val < r.val) {
        tmp.v1 = l.v1;
        tmp.v2 = l.v2;
        tmp.val = l.val;
    }
    else {
        tmp.v1 = r.v1;
        tmp.v2 = r.v2;
        tmp.val = r.val;
    }
    return tree[ind] = tmp;
}

ll query(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return INF;
    if (le <= start && end <= ri) return tree[ind].val;
    int mid = (start + end) / 2;
    return min(query(start, mid, ind * 2, le, ri), query(mid + 1, end, ind * 2 + 1, le, ri));
}

void solve() {
    ll i; cin >> n >> m >> c;
    for (i = 1; i <= n; i++) cin >> arr[i].x >> arr[i].y;
    if (n == 1) {
        cout << arr[1].x + arr[1].y - 1;
        return;
    }
    init(1, n, 1);
    dp[1] = arr[1].x + 2 * arr[1].y - 2;
    upt(1, n, 1, 1, dp[1], 0);
    //cout << dp[1] << ' ';
    //cout << '\n';
    ll maxf = arr[1].y;
    for (i = 2; i < n; i++) {
        ll k = bs1(1, n, 1, arr[i].x);
        //cout << k << ' ';
        upt1(1, n, 1, 1, k, arr[i].x);
        k = bs2(1, n, 1, arr[i].y * 2 - 2);
        //cout << k << ' ';
        upt2(1, n, 1, k, i - 1, arr[i].y * 2 - 2);
        dp[i] = query(1, n, 1, max(1LL, i - c), i - 1);
        maxf = max(maxf, arr[i].y);
        if (i <= c) dp[i] = min(dp[i], arr[i].x + maxf * 2 - 2);
        upt(1, n, 1, i, dp[i], 0);
        //cout << dp[i] << ' ';
        //cout << '\n';
    }
    maxf = 0;
    dp[n] = INF;
    for (i = n; i > max(n - c, 0LL); i--) {
        maxf = max(maxf, arr[i].y);
        dp[n] = min(dp[n], max(dp[i - 1], arr[n].x) + maxf - 1);
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
