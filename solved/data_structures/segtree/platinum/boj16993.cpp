#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct info {
	ll Max, Le, Ri, Sum;
};

int n, q;
info tree[400004];

info update(int start, int end, int ind, int i, int v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = {v,v,v,v};
    int mid = (start + end) / 2;
    info l = update(start, mid, ind * 2, i, v), r = update(mid + 1, end, ind * 2 + 1, i, v);
    info tmp;
    tmp.Sum = l.Sum + r.Sum;
    tmp.Le = max(l.Le, l.Sum + r.Le);
    tmp.Ri = max(l.Ri + r.Sum, r.Ri);
    tmp.Max = max(l.Ri + r.Le, max(l.Max, r.Max));
    return tree[ind] = tmp;
}

info res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return {-1000000001,0,0,0};
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    info l = res(start, mid, ind * 2, le, ri), r = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (l.Max == -1000000001) return r;
    else if (r.Max == -1000000001) return l;
    info tmp;
    tmp.Sum = l.Sum + r.Sum;
    tmp.Le = max(l.Le, l.Sum + r.Le);
    tmp.Ri = max(l.Ri + r.Sum, r.Ri);
    tmp.Max = max(l.Ri + r.Le, max(l.Max, r.Max));
    return tmp;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> a;
        update(1, n, 1, i, a);
    }
    cin >> q;
    while (q--) {
        cin >> a >> b;
        cout << res(1, n, 1, a, b).Max << '\n';
    }
}
