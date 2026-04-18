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
    int Le[2], Lecnt[2], Ri[2], Ricnt[2], Cnt;
};

int n, q, cnt;
int arr[100001], revnum[100001], num[100001], par[100001], sz[100001], top_[100001];
pii top[100001];
int dp[100001][2], dp_[100001][2];
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
    dp[ind][0]++;
    dp_[ind][0]++;
    top[ind] = {num[top_[ind]],num[top_[ind]]};
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs3(iter, ind);
        if (iter != g[ind][0]) dp[ind][0] += dp_[iter][0];
        dp_[ind][0] += dp_[iter][0];
    }
}

Info merge(Info a, Info b) {
    Info tmp;
    tmp.Le[0] = a.Le[0];
    tmp.Lecnt[0] = a.Lecnt[0];
    if (a.Lecnt[0] == a.Cnt) {
        if (b.Lecnt[0]) tmp.Le[0] += b.Le[0];
        tmp.Lecnt[0] += b.Lecnt[0];
    }
    tmp.Le[1] = a.Le[1];
    tmp.Lecnt[1] = a.Lecnt[1];
    if (a.Lecnt[1] == a.Cnt) {
        if (b.Lecnt[1]) tmp.Le[1] += b.Le[1];
        tmp.Lecnt[1] += b.Lecnt[1];
    }
    tmp.Ri[0] = b.Ri[0];
    tmp.Ricnt[0] = b.Ricnt[0];
    if (b.Ricnt[0] == b.Cnt) {
        if (a.Ricnt[0]) tmp.Ri[0] += a.Ri[0];
        tmp.Ricnt[0] += a.Ricnt[0];
    }
    tmp.Ri[1] = b.Ri[1];
    tmp.Ricnt[1] = b.Ricnt[1];
    if (b.Ricnt[1] == b.Cnt) {
        if (a.Ricnt[1]) tmp.Ri[1] += a.Ri[1];
        tmp.Ricnt[1] += a.Ricnt[1];
    }
    tmp.Cnt = a.Cnt + b.Cnt;
    return tmp;
}

Info init(int start, int end, int ind) {
    if (start == end) {
        return tree[ind] = {dp[revnum[end]][0],0,1,0,dp[revnum[end]][0],0,1,0,1};
    }
    int mid = (start + end) / 2;
    Info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = merge(l, r);
}

Info update(int start, int end, int ind, int i, int v1, int v2, int v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = {v1,v2,!v,v,v1,v2,!v,v,1};
    int mid = (start + end) / 2;
    Info l = update(start, mid, ind * 2, i, v1, v2, v);
    Info r = update(mid + 1, end, ind * 2 + 1, i, v1, v2, v);
    return tree[ind] = merge(l, r);
}

Info res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return tree[0];
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    Info l = res(start, mid, ind * 2, le, ri);
    Info r = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (mid < le) return r;
    if (ri <= mid) return l;
    return merge(l, r);
}

void update_path(int a) {
    arr[a] = !arr[a];
    dp[a][arr[a]]++;
    dp[a][!arr[a]]--;
    while (top_[a] != 1) {
        Info bef = res(1, n, 1, top[top_[a]].x, top[top_[a]].y);
        update(1, n, 1, num[a], dp[a][0], dp[a][1], arr[a]);
        Info aft = res(1, n, 1, top[top_[a]].x, top[top_[a]].y);
        //if (bef.Lecnt[arr[a]] == aft.Lecnt[arr[a]]) return;
        //우연히 같을 수 있기 때문에 무시해야됨
        dp[par[top_[a]]][0] += (aft.Lecnt[0] ? aft.Le[0] : 0) - (bef.Lecnt[0] ? bef.Le[0] : 0);
        dp[par[top_[a]]][1] += (aft.Lecnt[1] ? aft.Le[1] : 0) - (bef.Lecnt[1] ? bef.Le[1] : 0);
        a = par[top_[a]];
    }
    update(1, n, 1, num[a], dp[a][0], dp[a][1], arr[a]);
}

int res_path(int a) {
    while (top_[a] != 1) {
        Info l = res(1, n, 1, top[top_[a]].x, num[a]);
        Info r = res(1, n, 1, num[a], top[top_[a]].y);
        if (l.Lecnt[arr[a]] != l.Cnt || arr[par[top_[a]]] != arr[a]) return l.Ri[arr[a]] + r.Le[arr[a]] - dp[a][arr[a]];
        a = par[top_[a]];
    }
    Info l = res(1, n, 1, top[top_[a]].x, num[a]);
    Info r = res(1, n, 1, num[a], top[top_[a]].y);
    return l.Ri[arr[a]] + r.Le[arr[a]] - dp[a][arr[a]];
}

void solve() {
    int i, a, b; cin >> n;
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
    cin >> q;
    while (q--) {
        cin >> a >> b;
        if (a == 1) update_path(b);
        else cout << res_path(b) << '\n';
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
