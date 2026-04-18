#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct Info {
    ll le, ri, t;
};

struct Query {
    char a;
    int b, c;
};

int q;
Info tree[4000004];
Query query[300001];

Info merge(Info a, Info b) {
    if (b.le == b.ri) return a;
    if (a.le == b.ri) return b;
    if (a.ri <= b.le) return {a.le,b.ri,a.t + b.t + b.le - a.ri};
    if (a.ri - b.le > b.t) return {a.le,b.ri + a.ri - b.le - b.t, a.t};
    return {a.le,b.ri,a.t + b.t - a.ri + b.le};
}

Info init(int start, int end, int ind) {
    if (start == end) return tree[ind] = {end,end,0};
    int mid = (start + end) / 2;
    return tree[ind]= merge(init(start, mid, ind * 2), init(mid + 1, end, ind * 2 + 1));
}

Info update(int start, int end, int ind, int i, ll v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) {
        tree[ind].ri += v;
        return tree[ind];
    }
    int mid = (start + end) / 2;
    return tree[ind] = merge(update(start, mid, ind * 2, i, v), update(mid + 1, end, ind * 2 + 1, i, v));
}

Info q3(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return {0,0,0};
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    if (ri < mid) return q3(start, mid, ind * 2, le, ri);
    if (mid < le) return q3(mid + 1, end, ind * 2 + 1, le, ri);
    return merge(q3(start, mid, ind * 2, le, ri), q3(mid + 1, end, ind * 2 + 1, le, ri));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i; cin >> q;
    init(1, 1000000, 1);
    for (i = 1; i <= q; i++) {
        cin >> query[i].a >> query[i].b;
        if (query[i].a == '+') {
            cin >> query[i].c;
            update(1, 1000000, 1, query[i].b, query[i].c);
        }
        else if (query[i].a == '-') update(1, 1000000, 1, query[query[i].b].b, -query[query[i].b].c);
        else cout << max(q3(1, 1000000, 1, 1, query[i].b).ri, (ll)query[i].b) - query[i].b << '\n';
    }
}
