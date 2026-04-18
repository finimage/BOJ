/*
그냥 멍청해서 틀린거였구나
n이 1일 수가 있었네
*/
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct Info {
  int le[10], ri[10], Max[10], sum;  
};

int n, q, arr[100001], val[100001];
Info tree[270000], info0;

Info merge(Info& a, Info& b) {
    Info res;
    for (int i = 0; i < 10; i++) {
        res.le[i] = a.le[i];
        if (a.le[i] == a.sum) res.le[i] = a.le[i] + b.le[i];
        res.ri[i] = b.ri[i];
        if (b.ri[i] == b.sum) res.ri[i] = a.ri[i] + b.ri[i];
        res.Max[i] = max({a.Max[i],b.Max[i],a.ri[i] + b.le[i]});
        res.sum = a.sum + b.sum;
    }
    return res;
}

Info init(int start, int end, int ind) {
    if (start == end) {
        int k = arr[end + 1] - arr[end];
        val[end] = k;
        k = abs(k) - 1;
        if (0 <= k && k < 10) tree[ind].le[k] = tree[ind].ri[k] = tree[ind].Max[k] = 1;
        tree[ind].sum = 1;
        return tree[ind];
    }
    int mid = (start + end) / 2;
    Info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = merge(l, r);
}

Info update(int start, int end, int ind, int i, int v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) {
        int k = abs(val[end]) - 1;
        if (0 <= k && k < 10) tree[ind].le[k] = tree[ind].ri[k] = tree[ind].Max[k] = 0;
        val[end] += v;
        k = abs(val[end]) - 1;
        if (0 <= k && k < 10) tree[ind].le[k] = tree[ind].ri[k] = tree[ind].Max[k] = 1;
        return tree[ind];
    }
    int mid = (start + end) / 2;
    Info l = update(start, mid, ind * 2, i, v), r = update(mid + 1, end, ind * 2 + 1, i, v);
    return tree[ind] = merge(l, r);
}

Info q2(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return info0;
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    Info l = q2(start, mid, ind * 2, le, ri), r = q2(mid + 1, end, ind * 2 + 1, le, ri);
    return merge(l, r);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, a, b, c, d; cin >> n >> q;
    for (i = 1; i <= n; i++) cin >> arr[i];
    if (n == 1) {
        while (q--) {
            cin >> a >> b >> c >> d;
            if (a == 2) cout << "1\n";
        }
        return 0;
    }
    init(1, n - 1, 1);
    while (q--) {
        cin >> a >> b >> c >> d;
        if (a == 1) {
            if (d == 0) continue;
            if (b > 1) update(1, n - 1, 1, b - 1, d);
            if (c < n) update(1, n - 1, 1, c, -d);
        }
        else {
            if (b == c) {
                cout << "1\n";
                continue;
            }
            Info tmp = q2(1, n - 1, 1, b, c - 1);
            cout << tmp.Max[d - 1] + 1 << '\n';
        }
    }
}
