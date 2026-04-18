#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct info {
    ll le, ri, lecnt, ricnt, val, sz;
};


int n, q, arr[200001], lazy[800004];
info tree[800004];

void lazy_pro(int start, int end, int ind) {
    if (lazy[ind] % 2 == 0) {
        lazy[ind] = 0;
        return;
    }
    lazy[ind] = 0;
    tree[ind].le = 1 - tree[ind].le;
    tree[ind].ri = 1 - tree[ind].ri;
    if (start == end) return;
    lazy[ind * 2]++;
    lazy[ind * 2 + 1]++;
}

void init(int start, int end, int ind) {
    if (start == end) {
        tree[ind].le = tree[ind].ri = arr[end];
        tree[ind].lecnt = tree[ind].ricnt = tree[ind].val = 1;
        tree[ind].sz = 1;
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    if (tree[ind * 2].ricnt == mid - start + 1 && tree[ind * 2 + 1].lecnt == end - mid) {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind].ricnt = end - start + 1;
            tree[ind].val = (end - start + 1) * (end - start) / 2 + end - start + 1;
        }
    }
    else if (tree[ind * 2].ricnt != mid - start + 1 && tree[ind * 2 + 1].lecnt == end - mid) {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].lecnt + tree[ind * 2].ricnt;
            tree[ind].val = tree[ind * 2].val - tree[ind * 2].ricnt * (tree[ind * 2].ricnt - 1) / 2 - tree[ind * 2].ricnt + tree[ind].ricnt * (tree[ind].ricnt - 1) / 2 + tree[ind].ricnt;
        }
    }
    else if (tree[ind * 2].ricnt == mid - start + 1 && tree[ind * 2 + 1].lecnt != end - mid) {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind].lecnt * (tree[ind].lecnt - 1) / 2 + tree[ind].lecnt + tree[ind * 2 + 1].val - tree[ind * 2 + 1].lecnt * (tree[ind * 2 + 1].lecnt - 1) / 2 - tree[ind * 2 + 1].lecnt;
        }
    }
    else {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            ll k = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].val = k * (k - 1) / 2 + k + tree[ind * 2].val - tree[ind * 2].ricnt * (tree[ind * 2].ricnt - 1) / 2 - tree[ind * 2].ricnt + tree[ind * 2 + 1].val - tree[ind * 2 + 1].lecnt * (tree[ind * 2 + 1].lecnt - 1) / 2 - tree[ind * 2 + 1].lecnt;
        }
    }
    tree[ind].sz = tree[ind * 2].sz + tree[ind * 2 + 1].sz;
}

void update(int start, int end, int ind, int le, int ri) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        lazy[ind]++;
        lazy_pro(start, end, ind);
        return;
    }
    int mid = (start + end) / 2;
    update(start, mid, ind * 2, le, ri);
    update(mid + 1, end, ind * 2 + 1, le, ri);
    if (tree[ind * 2].ricnt == mid - start + 1 && tree[ind * 2 + 1].lecnt == end - mid) {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind].ricnt = end - start + 1;
            tree[ind].val = (end - start + 1) * (end - start) / 2 + end - start + 1;
        }
    }
    else if (tree[ind * 2].ricnt != mid - start + 1 && tree[ind * 2 + 1].lecnt == end - mid) {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].lecnt + tree[ind * 2].ricnt;
            tree[ind].val = tree[ind * 2].val - tree[ind * 2].ricnt * (tree[ind * 2].ricnt - 1) / 2 - tree[ind * 2].ricnt + tree[ind].ricnt * (tree[ind].ricnt - 1) / 2 + tree[ind].ricnt;
        }
    }
    else if (tree[ind * 2].ricnt == mid - start + 1 && tree[ind * 2 + 1].lecnt != end - mid) {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind].lecnt * (tree[ind].lecnt - 1) / 2 + tree[ind].lecnt + tree[ind * 2 + 1].val - tree[ind * 2 + 1].lecnt * (tree[ind * 2 + 1].lecnt - 1) / 2 - tree[ind * 2 + 1].lecnt;
        }
    }
    else {
        if (tree[ind * 2].ri == tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].val = tree[ind * 2].val + tree[ind * 2 + 1].val;
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            ll k = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].val = k * (k - 1) / 2 + k + tree[ind * 2].val - tree[ind * 2].ricnt * (tree[ind * 2].ricnt - 1) / 2 - tree[ind * 2].ricnt + tree[ind * 2 + 1].val - tree[ind * 2 + 1].lecnt * (tree[ind * 2 + 1].lecnt - 1) / 2 - tree[ind * 2 + 1].lecnt;
        }
    }
    tree[ind].sz = tree[ind * 2].sz + tree[ind * 2 + 1].sz;
}

info res(int start, int end, int ind, int le, int ri) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return {0,0,0,0,0,0};
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    info l = res(start, mid, ind * 2, le, ri), r = res(mid + 1, end, ind * 2 + 1, le, ri);
    info tmp;
    if (l.ricnt == mid - start + 1 && r.lecnt == end - mid) {
        if (l.ri == r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.val = l.val + r.val;
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = tmp.ricnt = l.sz + r.sz;
            tmp.val = tmp.lecnt * (tmp.lecnt - 1) / 2 + tmp.lecnt;
        }
    }
    else if (l.ricnt != mid - start + 1 && r.lecnt == end - mid) {
        if (l.ri == r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.val = l.val + r.val;
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = l.lecnt;
            tmp.ricnt = r.lecnt + l.ricnt;
            tmp.val = l.val - l.ricnt * (l.ricnt - 1) / 2 - l.ricnt + tmp.ricnt * (tmp.ricnt - 1) / 2 + tmp.ricnt;
        }
    }
    else if (l.ricnt == mid - start + 1 && r.lecnt != end - mid) {
        if (l.ri == r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.val = l.val + r.val;
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = l.ricnt + r.lecnt;
            tmp.ricnt = r.ricnt;
            tmp.val = tmp.lecnt * (tmp.lecnt - 1) / 2 + tmp.lecnt + r.val - r.lecnt * (r.lecnt - 1) / 2 - r.lecnt;
        }
    }
    else {
        if (l.ri == r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.val = l.val + r.val;
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = l.lecnt;
            tmp.ricnt = r.ricnt;
            ll k = l.ricnt + r.lecnt;
            tmp.val = k * (k - 1) / 2 + k + l.val - l.ricnt * (l.ricnt - 1) / 2 - l.ricnt + r.val - r.lecnt * (r.lecnt - 1) / 2 - r.lecnt;
        }
    }
    tmp.sz = l.sz + r.sz;
    return tmp;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b, c; cin >> n >> q;
    for (i = 1; i <= n; i++) cin >> arr[i];
    init(1, n, 1);
    while (q--) {
        cin >> a >> b >> c;
        if (a == 1) update(1, n, 1, b, c);
        else {
            cout << res(1, n, 1, b, c).val << '\n';
        }
    }
}
