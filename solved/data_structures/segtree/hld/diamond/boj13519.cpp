#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define inf 10000000000
using namespace std;

struct info {
    ll le, ri, Max, sum;
};

ll n, q, arr[100001], parent[100001], dep[100001], stsize[100001], num[100001], revnum[100001], top[100001], lazy[400004], cnt;
info tree[400004];
vector<vector<ll>> g;

void dfs1(int ind, int pre) {
    parent[ind] = pre;
    dep[ind] = dep[pre] + 1;
    stsize[ind]++;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs1(iter, ind);
        stsize[ind] += stsize[iter];
        if (stsize[iter] > stsize[g[ind][0]]) swap(g[ind][0], iter);
    }
}

void dfs2(int ind, int pre) {
    num[ind] = ++cnt;
    revnum[cnt] = ind;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        top[iter] = (iter == g[ind][0] ? top[ind] : iter);
        dfs2(iter, ind);
    }
}

void init(int start, int end, int ind) {
    lazy[ind] = 10001;
    if (start == end) {
        tree[ind] = {arr[revnum[end]],arr[revnum[end]],arr[revnum[end]],arr[revnum[end]]};
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    info l = tree[ind * 2], r = tree[ind * 2 + 1], tmp;
    tmp.le = max(l.le, l.sum + r.le);
    tmp.ri = max(r.ri, l.ri + r.sum);
    tmp.sum = l.sum + r.sum;
    tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
    tree[ind] = tmp;
}

void lazy_pro(int start, int end, int ind) {
    if (lazy[ind] == 10001) return;
    ll k = lazy[ind];
    lazy[ind] = 10001;
    tree[ind].sum = k * (ll)(end - start + 1);
    tree[ind].le = tree[ind].ri = tree[ind].Max = (k > 0 ? tree[ind].sum : k);
    if (start == end) return;
    lazy[ind * 2] = lazy[ind * 2 + 1] = k;
}

info res(int start, int end, int ind, int le, int ri) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return {-inf,-inf,-inf,0};
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    info l = res(start, mid, ind * 2, le, ri), r = res(mid + 1, end, ind * 2 + 1, le, ri), tmp;
    if (l.le == -inf) return r;
    if (r.le == -inf) return l;
    tmp.le = max(l.le, l.sum + r.le);
    tmp.ri = max(r.ri, l.ri + r.sum);
    tmp.sum = l.sum + r.sum;
    tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
    return tmp;
}

void update(int start, int end, int ind, int le, int ri, ll v) {
    lazy_pro(start, end, ind);
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        lazy[ind] = v;
        lazy_pro(start, end, ind);
        return;
    }
    int mid = (start + end ) / 2;
    update(start, mid, ind * 2, le, ri, v);
    update(mid + 1, end, ind * 2 + 1, le, ri, v);
    info l = tree[ind * 2], r = tree[ind * 2 + 1], tmp;
    tmp.le = max(l.le, l.sum + r.le);
    tmp.ri = max(r.ri, l.ri + r.sum);
    tmp.sum = l.sum + r.sum;
    tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
    tree[ind] = tmp;
}

ll res_path(ll a, ll b) {
    info aa = {-inf,-inf,-inf,0}, bb = {-inf,-inf,-inf,0};
    while (top[a] != top[b]) {
        if (dep[top[a]] > dep[top[b]]) {
            info l = res(1, n, 1, num[top[a]], num[a]), r = aa, tmp;
            if (l.le != -inf && r.ri != -inf) {
                tmp.le = max(l.le, l.sum + r.le);
                tmp.ri = max(r.ri, l.ri + r.sum);
                tmp.sum = l.sum + r.sum;
                tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
                aa = tmp;
            }
            else aa = l;
            a = parent[top[a]];
        }
        else {
            info l = res(1, n, 1, num[top[b]], num[b]), r = bb, tmp;
            if (l.le != -inf && r.ri != -inf) {
                tmp.le = max(l.le, l.sum + r.le);
                tmp.ri = max(r.ri, l.ri + r.sum);
                tmp.sum = l.sum + r.sum;
                tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
                bb = tmp;
            }
            else bb = l;
            b = parent[top[b]];
        }
    }
    if (dep[a] > dep[b]) {
        info l = res(1, n, 1, num[b], num[a]), r = aa, tmp;
        if (l.le != -inf && r.ri != -inf) {
            tmp.le = max(l.le, l.sum + r.le);
            tmp.ri = max(r.ri, l.ri + r.sum);
            tmp.sum = l.sum + r.sum;
            tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
            aa = tmp;
        }
        else aa = l;
    }
    else {
        info l = res(1, n, 1, num[a], num[b]), r = bb, tmp;
        if (l.le != -inf && r.ri != -inf) {
            tmp.le = max(l.le, l.sum + r.le);
            tmp.ri = max(r.ri, l.ri + r.sum);
            tmp.sum = l.sum + r.sum;
            tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
            bb = tmp;
        }
        else bb = l;
    }
    info l = aa, r = bb, tmp;
    swap(l.le, l.ri);
    if (l.le != -inf && r.ri != -inf) {
        tmp.le = max(l.le, l.sum + r.le);
        tmp.ri = max(r.ri, l.ri + r.sum);
        tmp.sum = l.sum + r.sum;
        tmp.Max = max(l.ri + r.le, max(l.Max, r.Max));
    }
    else if (l.le == -inf) tmp = r;
    else tmp = l;
    ll ans = tmp.Max;
    return (ans > 0 ? ans : 0);
}

void update_path(ll a, ll b, ll v) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        update(1, n, 1, num[top[a]], num[a], v);
        a = parent[top[a]];
    }
    if (dep[a] < dep[b]) swap(a, b);
    update(1, n, 1, num[b], num[a], v);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, a, b, c, d; cin >> n;
    g.resize(n + 1);
    for (i = 1; i <= n; i++) cin >> arr[i];
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs1(1, 0);
    top[1] = 1;
    dfs2(1, 0);
    init(1, n, 1);
    cin >> q;
    while (q--) {
        cin >> a >> b >> c;
        if (a == 1) cout << res_path(b, c) << '\n';
        else {
            cin >> d;
            update_path(b, c, d);
        }
    }
}
