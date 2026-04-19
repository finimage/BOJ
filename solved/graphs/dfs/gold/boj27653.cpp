#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n; ll ans;
vector<ll> arr;
vector<vector<int>> g;

void dfs(int ind, int pre) {
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs(iter, ind);
        if (arr[iter] > arr[ind]) ans += arr[iter] - arr[ind];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> n;
    arr.resize(n + 1);
    g.resize(n + 1);
    for (i = 1; i <= n; i++) cin >> arr[i];
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 1);
    cout << ans + arr[1];
}
