#include<iostream>
#define ll long long
using namespace std;

struct info {
    ll le, ri, sum, Max;
};

ll arr[100001];
info tree[400004];

void init(int start, int end, int ind) {
    if (start == end) {
        tree[ind] = { arr[end],arr[end],arr[end],arr[end] };
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    tree[ind].le = max(tree[ind * 2].le, tree[ind * 2].sum + tree[ind * 2 + 1].le);
    tree[ind].ri = max(tree[ind * 2 + 1].ri, tree[ind * 2 + 1].sum + tree[ind * 2].ri);
    tree[ind].sum = tree[ind * 2].sum + tree[ind * 2 + 1].sum;
    tree[ind].Max = max(max(tree[ind * 2].Max, tree[ind * 2 + 1].Max), tree[ind * 2].ri + tree[ind * 2 + 1].le);
}

info res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return { -100000000000,-100000000000,-100000000000,-100000000000 };
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    info a = res(start, mid, ind * 2, le, ri), b = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (a.Max != -100000000000 && b.Max != -100000000000) {
        info ret = { 0, };
        ret.le = max(a.le, a.sum + b.le);
        ret.ri = max(b.ri, a.ri + b.sum);
        ret.sum = a.sum + b.sum;
        ret.Max = max(max(a.Max, b.Max), a.ri + b.le);
        return ret;
    }
    if (b.Max == -100000000000) return a;
    if (a.Max == -100000000000) return b;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, i, x1, x2, y1, y2; cin >> n;
    for (i = 1; i <= n; i++) cin >> arr[i];
    init(1, n, 1);
    cin >> m;
    while (m--) {
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 < x2) cout << res(1, n, 1, x1, y1).ri + (y1 + 1 <= x2 - 1 ? res(1, n, 1, y1 + 1, x2 - 1).sum : 0) + res(1, n, 1, x2, y2).le << '\n';
        else {
            ll ans = -100000000000;
            ans = max(ans, res(1, n, 1, x2, y1).Max);
            if (x1 <= x2 - 1) ans = max(ans, res(1, n, 1, x1, x2 - 1).ri + res(1, n, 1, x2, y2).le);
            if (y1 + 1 <= y2) ans = max(ans, res(1, n, 1, x1, y1).ri + res(1, n, 1, y1 + 1, y2).le);
            cout << ans << '\n';
        }
    }
}
