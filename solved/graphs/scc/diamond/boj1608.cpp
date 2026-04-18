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

int n, cnt;
vector<vector<int>> udg, g;
set<int> ans, dep, indeg[100001];
bool visited[100001];
int num[100001], low[100001], cnt_, check[100001];
stack<int> st;

void dfs(int ind) {
    visited[ind] = 1; cnt++;
    for (auto& iter : udg[ind]) {
        if (visited[iter]) continue;
        dfs(iter);
    }
}

void scc(int ind) {
    num[ind] = low[ind] = ++cnt;
    st.push(ind);
    visited[ind] = 1;
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

void solve() {
    int i, j, a, b; cin >> n;
    udg.resize(n + 1);
    g.resize(n + 1);
    for (i = 1; i <= n; i++) {
        cin >> a;
        for (j = 0; j < a; j++) {
            cin >> b;
            g[i].push_back(b);
            indeg[b].insert(i);
            udg[i].push_back(b);
            udg[b].push_back(i);
        }
    }
    dfs(1);
    if (cnt != n) {
        cout << n << ' ';
        for (i = 1; i <= n; i++) cout << i << ' ';
        return;
    }
    cnt = 0;
    memset(visited, 0, sizeof(visited));
    for (i = 1; i <= n; i++) {
        if (!num[i]) scc(i);
    }
    if (cnt_ == 1) {
        cout << n << ' ';
        for (i = 1; i <= n; i++) cout << i << ' ';
        return;
    }
    vector<vector<int>> v(cnt_ + 1);
    for (i = 1; i <= n; i++) v[check[i]].push_back(i);
    for (i = cnt_; i >= 1; i--) {
        int tf = 0;
        for (auto& iter : v[i]) {
            int ccnt = 0;
            for (auto& itr : indeg[iter]) {
                if (ans.count(itr)) ccnt++;
            }
            if (ans.size() == 0 || ans.size() != ccnt) {
                tf = 1;
                break;
            }
        }
        dep.insert(i);
        if (tf) {
            for (auto& iter : dep) {
                for (auto& itr : v[iter]) ans.insert(itr);
            }
            dep.clear();
        }
    }
    cout << ans.size() << ' ';
    for (auto& iter : ans) cout << iter << ' ';
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
