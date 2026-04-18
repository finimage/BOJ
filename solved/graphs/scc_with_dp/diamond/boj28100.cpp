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

int n, m, arr[200002], cnt, cnt_;
ll ans;
vector<ll> dp;
vector<vector<int>> g;
vector<int> num, low, check;
bool visited[200002];
stack<int> st;

void scc(int ind) {
    num[ind] = low[ind] = ++cnt;
    visited[ind] = 1;
    st.push(ind);
    for (auto& iter : g[ind]) {
        if (!num[iter]) {
            scc(iter);
            low[ind] = min(low[ind], low[iter]);
        }
        else if (visited[iter]) low[ind] = min(low[ind], low[iter]);
    }
    if (num[ind] == low[ind]) {
        cnt_++;
        while (!st.empty()) {
            int k = st.top();
            st.pop();
            visited[k] = 0;
            check[k] = cnt_;
            if (k == ind) break;
        }
    }
}

void make_dp(int k) {
    int i;
    vector<vector<int>> gg(cnt_ + 1);
    vector<int> deg(cnt_ + 1);
    for (i = 1; i <= n + k; i++) gg[check[i]].push_back(i);
    dp.resize(cnt_ + 1);
    queue<int> q;
    q.push(check[1]);
    vector<bool> vis(cnt_ + 1);
    vis[check[1]] = 1;
    while (!q.empty()) {
        int a = q.front();
        q.pop();
        for (auto& iter : gg[a]) {
            for (auto& itr : g[iter]) {
                if (check[itr] == a) continue;
                deg[check[itr]]++;
                if (vis[check[itr]]) continue;
                vis[check[itr]] = 1;
                q.push(check[itr]);
            }
        }
    }
    q.push(check[1]);
    while (!q.empty()) {
        int a = q.front();
        q.pop();
        for (auto& iter : gg[a]) dp[a] += arr[iter];
        ans = max(ans, dp[a]);
        //cout << a << ' ' << dp[a] << '\n';
        for (auto& iter : gg[a]) {
            for (auto& itr : g[iter]) {
                if (check[itr] == a) continue;
                deg[check[itr]]--;
                if (deg[check[itr]] == 0) q.push(check[itr]);
                dp[check[itr]] = max(dp[check[itr]], dp[a]);
            }
        }
    }
    deg.clear();
    dp.clear();
    gg.clear();
    vis.clear();
}

void solve() {
    int i, a, b, x, y; cin >> n >> m;
    for (i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i + n] = arr[i];
    }
    g.resize(2 * n + 1);
    for (i = 0; i < m; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[a + n].push_back(b + n);
    }
    num.resize(2 * n + 1);
    low.resize(2 * n + 1);
    check.resize(2 * n + 1);
    for (i = 1; i <= n; i++) {
        if (!num[i]) scc(i);
    }
    make_dp(0);
    cin >> a >> x >> y;
    g[x + n].push_back(y + n);
    g[y + n].push_back(x + n);
    g[a].push_back(a + n);
    cnt = cnt_ = 0;
    for (i = n + 1; i <= n * 2; i++) {
        if (!num[i]) scc(i);
    }
    for (i = n + 1; i <= n * 2; i++) {
        if (check[i] == check[x + n] || check[i] == check[a + n]) arr[i - n] = 0;
    }
    cnt = cnt_ = 0;
    num.clear();
    low.clear();
    check.clear();
    num.resize(2 * n + 1);
    low.resize(2 * n + 1);
    check.resize(2 * n + 1);
    for (i = 1; i <= n * 2; i++) {
        if (!num[i]) scc(i);
    }
    make_dp(n);
    cout << ans;
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
