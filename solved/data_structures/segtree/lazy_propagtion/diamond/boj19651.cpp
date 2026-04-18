#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct info {
    ll le, ri;
    int le_cnt, ri_cnt, Max_cnt;
};

int n;
info tree[400004];
ll arr[100001], lazy[400004];

void lazy_pro(int start, int end, int ind) {
    if (lazy[ind]) {
        ll k = lazy[ind];
        lazy[ind] = 0;
        tree[ind].le += k;
        tree[ind].ri += k;
        if (start == end) return;
        lazy[ind * 2] += k;
        lazy[ind * 2 + 1] += k;
    }
}

info init(int start, int end, int ind) {
    if (start == end) return tree[ind] = {arr[start],arr[start],1,1,1};
    int mid = (start + end) / 2;
    info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    if (l.ri == r.le) {
        if (l.le_cnt == mid - start + 1) l.le_cnt += r.le_cnt;
        if (r.ri_cnt == end - mid) r.ri_cnt += l.ri_cnt;
        int Max = max(l.Max_cnt,r.Max_cnt);
        Max = max(max(Max, l.ri_cnt + r.le_cnt), max(l.le_cnt, r.ri_cnt));
        return tree[ind] = {l.le,r.ri,l.le_cnt,r.ri_cnt,Max};
    }
    else return tree[ind] = {l.le,r.ri,l.le_cnt,r.ri_cnt,max(l.Max_cnt,r.Max_cnt)};
}

info update(int start, int end, int ind, int le, int ri, int v) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        tree[ind].le += v;
        tree[ind].ri += v;
        if (start == end) return tree[ind];
        lazy[ind * 2] += v;
        lazy[ind * 2 + 1] += v;
        return tree[ind];
    }
    int mid = (start + end) / 2;
    info l = update(start, mid, ind * 2, le, ri, v), r = update(mid + 1, end, ind * 2 + 1, le, ri, v);
    if (l.ri == r.le) {
        if (l.le_cnt == mid - start + 1) l.le_cnt += r.le_cnt;
        if (r.ri_cnt == end - mid) r.ri_cnt += l.ri_cnt;
        int Max = max(l.Max_cnt,r.Max_cnt);
        Max = max(max(Max, l.ri_cnt + r.le_cnt), max(l.le_cnt, r.ri_cnt));
        return tree[ind] = {l.le,r.ri,l.le_cnt,r.ri_cnt,Max};
    }
    else return tree[ind] = {l.le,r.ri,l.le_cnt,r.ri_cnt,max(l.Max_cnt,r.Max_cnt)};
}

info res(int start, int end, int ind, int le, int ri) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return {(ll)1e12,(ll)1e12,0,0,0};
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    info l = res(start, mid, ind * 2, le, ri), r = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (l.le_cnt == 0) return r;
    else if (r.le_cnt == 0) return l;
    else if (l.ri == r.le) {
        if (l.le_cnt == mid - start + 1) l.le_cnt += r.le_cnt;
        if (r.ri_cnt == end - mid) r.ri_cnt += l.ri_cnt;
        int Max = max(l.Max_cnt,r.Max_cnt);
        Max = max(max(Max, l.ri_cnt + r.le_cnt), max(l.le_cnt, r.ri_cnt));
        return {l.le,r.ri,l.le_cnt,r.ri_cnt,Max};
    }
    else return {l.le,r.ri,l.le_cnt,r.ri_cnt,max(l.Max_cnt,r.Max_cnt)};
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, q, a, b, c, d, e; cin >> n;
    for (i = 1; i <= n; i++) cin >> arr[i];
    for (i = n; i > 1; i--) arr[i] -= arr[i - 1];
    init(1, n, 1);
    cin >> q;
    while (q--) {
        cin >> a >> b >> c;
        if (a == 2) cout << res(1, n, 1, b + 1, c).Max_cnt + 1 << '\n';
        else {
            cin >> d >> e;
            update(1, n, 1, b, b, d);
            update(1, n, 1, b + 1, c, e);
            update(1, n, 1, c + 1, c + 1, -(ll)d - (ll)e * (c - b));
        }
    }
}
