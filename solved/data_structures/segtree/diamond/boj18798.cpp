#include<iostream>
using namespace std;

struct info {
    int cnt, and_;
    bool check;
};

int n, k, arr[250001];
info tree[1000001];

info init(int start, int end, int ind) {
    if (start == end) {
        if (k == arr[start]) return tree[ind] = { 1,arr[start],1 };
        else if (k == (arr[start] | k)) return tree[ind] = { 0,arr[start],1 };
        else return tree[ind] = { 0,arr[start],0 };
    }
    int mid = (start + end) / 2;
    info le = init(start, mid, ind * 2), ri = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = { le.cnt + ri.cnt,le.and_ & ri.and_,le.check || ri.check };
}

info update(int start, int end, int ind, int le, int ri, int x) {
    if (ri < start || end < le) return tree[ind];
    if (tree[ind].check == 0) return tree[ind];
    if (k == (x | k)) {
        if ((tree[ind].and_ | x) == tree[ind].and_) return tree[ind];
        if (start == end) {
            if ((tree[ind].and_ | x) == k) return tree[ind] = { 1,tree[ind].and_ | x,1 };
            else return tree[ind] = { 0,tree[ind].and_ | x,1 };
        }
        int mid = (start + end) / 2;
        info l = update(start, mid, ind * 2, le, ri, x), r = update(mid + 1, end, ind * 2 + 1, le, ri, x);
        return tree[ind] = { l.cnt + r.cnt,l.and_ & r.and_,l.check || r.check };
    }
    else {
        if (le <= start && end <= ri) return tree[ind] = { 0,tree[ind].and_ & x,0 };
        int mid = (start + end) / 2;
        info l = update(start, mid, ind * 2, le, ri, x), r = update(mid + 1, end, ind * 2 + 1, le, ri, x);
        return tree[ind] = { l.cnt + r.cnt,l.and_ & r.and_,l.check || r.check };
    }
}

int res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return 0;
    if (tree[ind].check == 0) return 0;
    if (le <= start && end <= ri) return tree[ind].cnt;
    int mid = (start + end) / 2;
    return res(start, mid, ind * 2, le, ri) + res(mid + 1, end, ind * 2 + 1, le, ri);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, q, a, l, r, x; cin >> n >> k;
    for (i = 1; i <= n; i++) cin >> arr[i];
    init(1, n, 1);
    cin >> q;
    while (q--) {
        cin >> a >> l >> r;
        if (a == 1) {
            cin >> x;
            update(1, n, 1, l, r, x);
        }
        else cout << res(1, n, 1, l, r) << '\n';
    }
}
