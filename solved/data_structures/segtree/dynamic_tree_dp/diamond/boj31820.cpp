#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

struct Info {
    ll Le, Ri, Max, Sum;
};

int n, q, cnt;
int arr[100001], revnum[100001], num[100001], par[100001], sz[100001], top_[100001];
pii top[100001];
ll dp[100001], dp_[100001];
ll tree_[400004];
vector<vector<int>> g;
Info tree[400004];

void dfs1(int ind, int pre) {
    par[ind] = pre;
    sz[ind]++;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs1(iter, ind);
        sz[ind] += sz[iter];
        if (sz[iter] > sz[g[ind][0]]) swap(iter, g[ind][0]);
    }
}

void dfs2(int ind, int pre) {
    num[ind] = ++cnt;
    revnum[cnt] = ind;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        top_[iter] = g[ind][0] == iter ? top_[ind] : iter;
        dfs2(iter, ind);
    }
}

void dfs3(int ind, int pre) {
    dp[ind] += arr[ind];
    dp_[ind] += arr[ind];
    top[ind] = {num[top_[ind]],num[top_[ind]]};
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs3(iter, ind);
        if (g[ind][0] != iter) dp[ind] += max((ll)0, dp_[iter]);
        dp_[ind] += max((ll)0, dp_[iter]);
    }
}

Info merge(Info a, Info b) {
    Info tmp;
    tmp.Le = max(a.Le, a.Sum + b.Le);
    tmp.Ri = max(b.Ri, a.Ri + b.Sum);
    tmp.Max = max({a.Max,b.Max,a.Ri+b.Le});
    tmp.Sum = a.Sum + b.Sum;
    return tmp;
}

Info init(int start, int end, int ind) {
    tree_[ind] = -2e9;
    if (start == end) return tree[ind] = {dp[revnum[end]],dp[revnum[end]],dp[revnum[end]],dp[revnum[end]]};
    int mid = (start + end) / 2;
    Info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = merge(l, r);
}

Info update(int start, int end, int ind, int i, ll v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = {v,v,v,v};
    int mid = (start + end) / 2;
    Info l = update(start, mid, ind * 2, i, v);
    Info r = update(mid + 1, end, ind * 2 + 1, i, v);
    return tree[ind] = merge(l, r);
}

Info res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return {0,0,0,0};
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    Info l = res(start, mid, ind * 2, le, ri);
    Info r = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (mid < le) return r;
    if (ri <= mid) return l;
    return merge(l, r);
}

ll upd(int start, int end, int ind, int i, ll v) {
    if (i < start || end < i) return tree_[ind];
    if (start == end) return tree_[ind] = v;
    int mid = (start + end) / 2;
    return tree_[ind] = max(upd(start, mid, ind * 2, i, v), upd(mid + 1, end, ind * 2 + 1, i, v));
}

void update_path(int a, ll v) {
    dp[a] += v - arr[a];
    arr[a] = v;
    while (top_[a] != 1) {
        ll tmp1 = res(1, n, 1, top[top_[a]].x, top[top_[a]].y).Le;
        update(1, n, 1, num[a], dp[a]);
        Info aft = res(1, n, 1, top[top_[a]].x, top[top_[a]].y);
        ll tmp2 = aft.Le;
        upd(1, n, 1, top_[a], aft.Max);
        if (tmp2 > 0 && tmp1 > 0) dp[par[top_[a]]] += tmp2 - tmp1;
        if (tmp2 <= 0 && tmp1 > 0) dp[par[top_[a]]] -= tmp1;
        if (tmp1 <= 0 && tmp2 > 0) dp[par[top_[a]]] += tmp2;
        a = par[top_[a]];
    }
    update(1, n, 1, num[a], dp[a]);
    upd(1, n, 1, top_[a], res(1, n, 1, top[top_[a]].x, top[top_[a]].y).Max);
}

void solve() {
    int i, a, b; cin >> n;
    for (i = 1; i <= n; i++) cin >> arr[i];
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs1(1, 0);
    top[1] = {1,1};
    top_[1] = 1;
    dfs2(1, 0);
    dfs3(1, 0);
    for (i = 1; i <= n; i++) top[top_[i]].y = max(top[top_[i]].y, num[i]);
    init(1, n, 1);
    for (i = 1; i <= n; i++) {
        if (i == top_[i]) upd(1, n, 1, i, res(1, n, 1, top[i].x, top[i].y).Max);
    }
    cin >> q;
    while (q--) {
        cin >> a >> b;
        update_path(a, b);
        cout << tree_[1] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
