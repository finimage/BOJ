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

int n, m, arr[50001];
int num[500050], low[500050], cnt, cnt_, check[500050];
bool visited[500050];
vector<vector<int>> g;
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

void solve() {
    int i, j, t, x, y, z; char c; cin >> n;
    g.resize(n * 10 + 10);
    for (i = 1; i <= n; i++) {
        cin >> arr[i];
        if (arr[i]) {
            x = arr[i];
            for (j = 0; j < 5; j++) {
                int a = i * 5 - 4 + j;
                if (x & 1) g[a * 2].push_back(a * 2 - 1);
                else g[a * 2 - 1].push_back(a * 2);
                x >>= 1;
            }
        }
        int a = i * 5, b = i * 5 - 1, c = i * 5 - 2;
        g[a * 2 - 1].push_back(b * 2);
        g[b * 2 - 1].push_back(a * 2);
        g[c * 2 - 1].push_back(a * 2);
        g[a * 2].push_back(b * 2 - 1);
        g[b * 2].push_back(a * 2 - 1);
        g[a * 2 - 1].push_back(c * 2);
    }
    cin >> m;
    for (i = 0; i < m; i++) {
        cin >> c >> x >> y >> z;
        if (c == '&') {
            for (j = 0; j < 5; j++) {
                int a = x * 5 - 4 + j, b = y * 5 - 4 + j;
                if (z & 1) {
                    g[a * 2].push_back(a * 2 - 1);
                    g[b * 2].push_back(b * 2 - 1);
                }
                else {
                    g[a * 2 - 1].push_back(b * 2);
                    g[b * 2 - 1].push_back(a * 2);
                }
                z >>= 1;
            }
        }
        else {
            for (j = 0; j < 5; j++) {
                int a = x * 5 - 4 + j, b = y * 5 - 4 + j;
                if (z & 1) {
                    g[a * 2].push_back(b * 2 - 1);
                    g[b * 2].push_back(a * 2 - 1);
                }
                else {
                    g[a * 2 - 1].push_back(a * 2);
                    g[b * 2 - 1].push_back(b * 2);
                }
                z >>= 1;
            }
        }
    }
    for (i = 1; i <= n * 10; i++) {
        if (!num[i]) scc(i);
    }
    vector<int> ans(n + 1);
    for (i = 1; i <= n; i++) {
        int tmp = 0;
        for (j = 0; j < 5; j++) {
            int a = i * 5 - 4 + j;
            if (check[a * 2 - 1] == check[a * 2]) {
                cout << "0";
                return;
            }
            if (check[a * 2 - 1] < check[a * 2]) tmp |= (1 << j);
        }
        ans[i] = tmp;
    }
    cout << "1\n";
    for (i = 1; i <= n; i++) cout << ans[i] << ' ';
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
