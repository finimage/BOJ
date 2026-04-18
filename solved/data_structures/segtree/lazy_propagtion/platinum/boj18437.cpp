#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, m, cnt;
int num[100001], sz[100001];
vector<int> g[100001];
int tree[400004];
int lazy[400004];

void dfs(int ind) {
    num[ind] = ++cnt;
    sz[ind] = 1;
    for (auto& iter : g[ind]) {
        dfs(iter);
        sz[ind] += sz[iter];
    }
}

void lazy_prop(int start, int end, int ind) {
    if (!lazy[ind]) return;
    int k = lazy[ind];
    lazy[ind] = 0;
    if (k == 1) tree[ind] = end - start + 1;
    else tree[ind] = 0;
    if (start == end) return;
    lazy[ind * 2] = lazy[ind * 2 + 1] = k;
}

int update(int start, int end, int ind, int le, int ri, int t) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        lazy[ind] = t;
        lazy_prop(start, end, ind);
        return tree[ind];
    }
    int mid = (start + end) / 2;
    return tree[ind] = update(start, mid, ind * 2, le, ri, t) + update(mid + 1, end, ind * 2 + 1, le, ri, t);
}

int res(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return 0;
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    return res(start, mid, ind * 2, le, ri) + res(mid + 1, end, ind * 2 + 1, le, ri);
}

void solve() {
    int i, a, b; cin >> n >> a;
    for (i = 2; i <= n; i++) {
        cin >> a;
        g[a].push_back(i);
    }
    dfs(1);
    cin >> m;
    while (m--) {
        cin >> a >> b;
        if (a == 1) update(1, n, 1, num[b] + 1, num[b] + sz[b] - 1, -1);
        else if (a == 2) update(1, n, 1, num[b] + 1, num[b] + sz[b] - 1, 1);
        else cout << sz[b] - 1 - res(1, n, 1, num[b] + 1, num[b] + sz[b] - 1) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
