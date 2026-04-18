#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

struct info {
    int q;
    ll l, r;
};

int n, tree[2400020];
pii lazy[2400020];
ll arr[600010];
vector<ll> v;
vector<info> query;

void lazy_pro(int start, int end, int ind) {
    if (lazy[ind].x == -1) {
        if (lazy[ind].y % 2) {
            lazy[ind].y = 0;
            tree[ind] = end - start + 1 - tree[ind];
            if (start == end) return;
            if (lazy[ind * 2].x == -1) lazy[ind * 2].y++;
            else lazy[ind * 2] = {lazy[ind * 2].x == 0,0};
            if (lazy[ind * 2 + 1].x == -1) lazy[ind * 2 + 1].y++;
            else lazy[ind * 2 + 1] = {lazy[ind * 2 + 1].x == 0,0};
        }
    }
    else {//?
        int k = lazy[ind].x;
        tree[ind] = (end - start + 1) * k;
        lazy[ind] = {-1,0};
        if (start == end) return;
        lazy[ind * 2] = {k,0};
        lazy[ind * 2 + 1] = {k,0};
    }
}

void init(int start, int end, int ind) {
    lazy[ind].x = -1;
    if (start == end) return;
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
}

int update(int start, int end, int ind, int le, int ri, int x) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        if (x == -1) {
            tree[ind] = end - start + 1 - tree[ind];
            if (start == end) return tree[ind];
            if (lazy[ind * 2].x == -1) lazy[ind * 2].y++;
            else lazy[ind * 2] = {lazy[ind * 2].x == 0,0};
            if (lazy[ind * 2 + 1].x == -1) lazy[ind * 2 + 1].y++;
            else lazy[ind * 2 + 1] = {lazy[ind * 2 + 1].x == 0,0};
            return tree[ind];
        }
        else {
            tree[ind] = (end - start + 1) * x;
            lazy[ind] = {-1,0};
            if (start == end) return tree[ind];
            lazy[ind * 2] = {x,0};
            lazy[ind * 2 + 1] = {x,0};
            return tree[ind];
        }
    }
    int mid = (start + end) / 2;
    return tree[ind] = update(start, mid, ind * 2, le, ri, x) + update(mid + 1, end, ind * 2 + 1, le, ri ,x);
}

ll res(int start, int end, int ind) {
    lazy_pro(start, end, ind);
    if (start == end) {
        if (tree[ind]) return arr[start] + 1;
        else return arr[start];
    }
    int mid = (start + end) / 2;
    lazy_pro(start, mid, ind * 2);
    lazy_pro(mid + 1, end, ind * 2 + 1);
    if (mid - start + 1 == tree[ind * 2]) return res(mid + 1, end, ind * 2 + 1);
    else return res(start, mid, ind * 2);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j = 1, l, N; cin >> n;
    query.resize(n);
    v.push_back(1);
    for (i = 0; i < n; i++) {
        cin >> query[i].q >> query[i].l >> query[i].r;
        v.push_back(query[i].l);
        v.push_back(query[i].r);
    }
    sort(v.begin(), v.end());
    l = v.size();
    for (i = 0; i < l; i++) {
        if (i > 0 && v[i] == v[i - 1]) continue;
        if (v[i] == 1) {
            arr[j++] = 1;
            arr[j++] = 2;
        }
        else if (arr[j - 1] == v[i]) arr[j++] = v[i] + 1;
        else if (arr[j - 1] == v[i] - 1) {
            arr[j++] = v[i];
            arr[j++] = v[i] + 1;
        }
        else {
            arr[j++] = v[i] - 1;
            arr[j++] = v[i];
            arr[j++] = v[i] + 1;
        }
    }
    for (i = 0; i < n; i++) {
        query[i].l = lower_bound(arr, arr + j, query[i].l) - arr;
        query[i].r = lower_bound(arr, arr + j, query[i].r) - arr;
    }
    N = j - 1;
    init(1, N, 1);
    for (i = 0; i < n; i++) {
        if (query[i].q == 1) update(1, N, 1, query[i].l, query[i].r, 1);
        else if (query[i].q == 2) update(1, N, 1, query[i].l, query[i].r, 0);
        else update(1, N, 1, query[i].l, query[i].r, -1);
        cout << res(1, N, 1) << '\n';
    }
}
