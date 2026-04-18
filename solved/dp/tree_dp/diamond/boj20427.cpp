#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, m, num[1000001], low[1000001], cnt, cnt_, check[1000001];
ll dp[1000001][2];
bool visited[1000001];
stack<int> st;
vector<vector<int>> cycle;
vector<vector<pll>> g;

void scc(int ind, int pre) {
    num[ind] = low[ind] = ++cnt;
    visited[ind] = 1;
    st.push(ind);
    for (auto& iter : g[ind]) {
        if (iter.x == pre) continue;
        if (!num[iter.x]) {
            scc(iter.x, ind);
            low[ind] = min(low[ind], low[iter.x]);
        }
        else if (visited[iter.x]) low[ind] = min(low[ind], low[iter.x]);
    }
    if (num[ind] == low[ind]) {
        if (!st.empty() && st.top() == ind) st.pop();
        else {
            vector<int> tmp;
            cnt_++;
            while (!st.empty()) {
                int k = st.top();
                st.pop();
                visited[k] = 0;
                check[k] = cnt_;
                tmp.push_back(k);
                if (k == ind) break;
            }
            cycle.emplace_back(tmp);
        }
    }
}

ll dfs(int ind, int pre) {
    ll res = 0;
    for (auto& iter : g[ind]) {
        if (iter.x == pre) continue;
        if (check[ind] && check[ind] == check[iter.x]) continue;
        ll k = dfs(iter.x, ind);
        if (k == 0) res += iter.y;
        else res += min(k, iter.y);
    }
    return res;
}

void process(int ind) {
    int i, l = cycle[ind].size();
    vector<ll> tmp, v, psum(l, 0), dpdp(l, 0);
    ll res = 0, spsize = (ll)l * (ll)l;
    for (i = 0; i + 1 < l; i++) {
        ll k = dfs(cycle[ind][i], 0);
        tmp.push_back(k);
        res += tmp.back();
        psum[i] = res;
    }
    for (i = 0; i < l; i++) {
        for (auto& iter : g[cycle[ind][i]]) {
            if (iter.x == cycle[ind][(i - 1 + l) % l]) {
                v.push_back(iter.y);
                break;
            }
        }
        if (i == 0) dpdp[i] = v.back();
        else dpdp[i] = min(dpdp[i - 1], v.back() + psum[i - 1]);
    }
    ll vv = 0;
    for (i = l - 1; i > 0; i--) {
        if (res > dpdp[i - 1] + v[i] + vv) {
            res = dpdp[i - 1] + v[i] + vv;
            spsize = 0;
        }
        vv += tmp[i - 1];
    }
    g[cycle[ind].back()].clear();
    dp[cycle[ind].back()][0] = spsize;
    dp[cycle[ind].back()][1] = res;
}

void dfs_(int ind, int pre, ll val) {
    ll tmp = dp[ind][1];
    for (auto& iter : g[ind]) {
        if (iter.x == pre) continue;
        dfs_(iter.x, ind, iter.y);
        dp[ind][0] += dp[iter.x][0];
        tmp += dp[iter.x][1];
    }
    if (val && val < tmp) {
        dp[ind][0] = 0;
        dp[ind][1] = val;
    }
    else if (tmp == 0) dp[ind][1] = val;
    else dp[ind][1] = tmp;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, a, b, c; cin >> n >> m;
    g.resize(n + 1);
    for (i = 0; i < m; i++) {
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    scc(1, 0);
    for (i = 0; i < cycle.size(); i++) process(i);
    dfs_(1, 0, 0);
    cout << dp[1][0];
}
