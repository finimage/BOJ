#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n;
int arr[100001];
vector<int> g[100001];
int cnt[100001];
ll sum_[100001];

void tree_dp(int ind, int pre) {
    sum_[ind] += arr[ind];
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        tree_dp(iter, ind);
        cnt[ind] += cnt[iter];
        sum_[ind] += sum_[iter];
    }
    if (sum_[ind] > 0) cnt[ind] = max(cnt[ind], 1);
}

void solve() {
    int i, a, b; cin >> n;
    for (i = 1; i <= n; i++) cin >> arr[i];
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll s = 0, tmp = -1;
    for (i = 1; i <= n; i++) {
        if (arr[i] < 0) tmp = i;
        s += arr[i];
    }
    if (s) cout << -1;
    else if (tmp == -1) cout << 0;
    else {
        tree_dp(tmp, 0);
        cout << cnt[tmp];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
