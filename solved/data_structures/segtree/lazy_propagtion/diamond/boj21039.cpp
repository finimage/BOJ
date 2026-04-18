#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct info {
    ll le, ri, lecnt, ricnt, maxcnt, sz;
};

string s;
int n, q, lazy[400004];
info tree[400004];

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
        tree[ind].le = tree[ind].ri = s[end - 1] - '0';
        tree[ind].lecnt = tree[ind].ricnt = tree[ind].maxcnt = 1;
        tree[ind].sz = 1;
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    if (tree[ind * 2].ricnt == mid - start + 1 && tree[ind * 2 + 1].lecnt == end - mid) {
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind].ricnt = tree[ind].maxcnt = end - start + 1;
        }
    }
    else if (tree[ind * 2].ricnt != mid - start + 1 && tree[ind * 2 + 1].lecnt == end - mid) {
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].lecnt + tree[ind * 2].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, max(tree[ind].lecnt, tree[ind].ricnt));
        }
    }
    else if (tree[ind * 2].ricnt == mid - start + 1 && tree[ind * 2 + 1].lecnt != end - mid) {
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2 + 1].maxcnt, max(tree[ind].lecnt, tree[ind].ricnt));
        }
    }
    else {
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            ll k = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].maxcnt = max(k, max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt));
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
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind].ricnt = tree[ind].maxcnt = end - start + 1;
        }
    }
    else if (tree[ind * 2].ricnt != mid - start + 1 && tree[ind * 2 + 1].lecnt == end - mid) {
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].lecnt + tree[ind * 2].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, max(tree[ind].lecnt, tree[ind].ricnt));
        }
    }
    else if (tree[ind * 2].ricnt == mid - start + 1 && tree[ind * 2 + 1].lecnt != end - mid) {
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2 + 1].maxcnt, max(tree[ind].lecnt, tree[ind].ricnt));
        }
    }
    else {
        if (tree[ind * 2].ri != tree[ind * 2 + 1].le) {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            tree[ind].maxcnt = max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt);
        }
        else {
            tree[ind].le = tree[ind * 2].le;
            tree[ind].ri = tree[ind * 2 + 1].ri;
            tree[ind].lecnt = tree[ind * 2].lecnt;
            tree[ind].ricnt = tree[ind * 2 + 1].ricnt;
            ll k = tree[ind * 2].ricnt + tree[ind * 2 + 1].lecnt;
            tree[ind].maxcnt = max(k, max(tree[ind * 2].maxcnt, tree[ind * 2 + 1].maxcnt));
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
        if (l.ri != r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.maxcnt = max(l.maxcnt, r.maxcnt);
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = tmp.ricnt = tmp.maxcnt = l.sz + r.sz;
        }
    }
    else if (l.ricnt != mid - start + 1 && r.lecnt == end - mid) {
        if (l.ri != r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.maxcnt = max(l.maxcnt, r.maxcnt);
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = l.lecnt;
            tmp.ricnt = r.lecnt + l.ricnt;
            tmp.maxcnt = max(l.maxcnt, max(tmp.lecnt, tmp.ricnt));
        }
    }
    else if (l.ricnt == mid - start + 1 && r.lecnt != end - mid) {
        if (l.ri != r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.maxcnt = max(l.maxcnt, r.maxcnt);
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = l.ricnt + r.lecnt;
            tmp.ricnt = r.ricnt;
            tmp.maxcnt = max(r.maxcnt, max(tmp.lecnt, tmp.ricnt));
        }
    }
    else {
        if (l.ri != r.le) {
            tmp.le = l.le;
            tmp.lecnt = l.lecnt;
            tmp.ri = r.ri;
            tmp.ricnt = r.ricnt;
            tmp.maxcnt = max(l.maxcnt, r.maxcnt);
        }
        else {
            tmp.le = l.le;
            tmp.ri = r.ri;
            tmp.lecnt = l.lecnt;
            tmp.ricnt = r.ricnt;
            ll k = l.ricnt + r.lecnt;
            tmp.maxcnt = max(k, max(l.maxcnt, r.maxcnt));
        }
    }
    tmp.sz = l.sz + r.sz;
    return tmp;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b, c; cin >> n >> q;
    cin >> s;
    init(1, n, 1);
    while (q--) {
        cin >> a >> b >> c;
        if (a == 1) update(1, n, 1, b, c);
        else {
            cout << res(1, n, 1, b, c).maxcnt << '\n';
        }
    }
}
