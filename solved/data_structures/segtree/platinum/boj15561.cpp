#include<iostream>
using namespace std;

struct info {
    int le, ri, sum, Max;
};

int arr[100001], v;
info tree[400004];

info init(int start, int end, int ind) {
    if (start == end) return tree[ind] = { arr[end],arr[end],arr[end],arr[end] };
    int mid = (start + end) / 2;
    info a = init(start, mid, ind * 2), b = init(mid + 1, end, ind * 2 + 1);
    tree[ind].le = max(a.le, a.sum + v + b.le);
    tree[ind].ri = max(b.ri, b.sum + v + a.ri);
    tree[ind].sum = a.sum + v + b.sum;
    tree[ind].Max = max(max(a.Max, b.Max), a.ri + v + b.le);
    return tree[ind];
}

info res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return { -100000000,-100000000,-100000000,-100000000 };
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    info a = res(start, mid, ind * 2, le, ri), b = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (a.Max != -100000000 && b.Max != -100000000) {
        info ret = { 0, };
        ret.le = max(a.le, a.sum + v + b.le);
        ret.ri = max(b.ri, a.ri + v + b.sum);
        ret.sum = a.sum + v + b.sum;
        ret.Max = max(max(a.Max, b.Max), a.ri + v + b.le);
        return ret;
    }
    if (b.Max == -100000000) return a;
    if (a.Max == -100000000) return b;
}

info update(int start, int end, int ind, int i) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = { arr[end],arr[end],arr[end],arr[end] };
    int mid = (start + end) / 2;
    info a = update(start, mid, ind * 2, i), b = update(mid + 1, end, ind * 2 + 1, i);
    tree[ind].le = max(a.le, a.sum + v + b.le);
    tree[ind].ri = max(b.ri, b.sum + v + a.ri);
    tree[ind].sum = a.sum + v + b.sum;
    tree[ind].Max = max(max(a.Max, b.Max), a.ri + v + b.le);
    return tree[ind];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q, u, i, a, b, c; cin >> n >> q >> u >> v;
    for (i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] *= u;
    }
    init(1, n, 1);
    while (q--) {
        cin >> c >> a >> b;
        if (c == 0) cout << res(1, n, 1, a, b).Max << '\n';
        else {
            arr[a] = b * u;
            update(1, n, 1, a);
        }
    }
}
