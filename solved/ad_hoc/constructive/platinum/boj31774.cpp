#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n;
vector<int> v, arr, ans;

void solve() {
    int i, cnt = 0; cin >> n;
    v.clear();
    v.resize(n + 1);
    arr.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> arr[i];
        v[arr[i]]++;
        if (v[arr[i]] == 1) cnt++;
    }
    if ((cnt == n - 2 && v[1] != 2) || cnt < n - 2 || arr[n - 1] != 1) {
        cout << "-1\n";
        return;
    }
    ans.resize(n + 1);
    if (cnt == n - 2 && v[1] == 2) {
        vector<int> tmp;
        for (i = 1; i <= n; i++) {
            if (!v[i]) tmp.emplace_back(i);
        }
        ans[1] = tmp[0];
        ans[n] = tmp[1];
        int le = 1, ri = n;
        for (i = 1; i < n; i++) {
            if (ans[le] < ans[ri]) ans[--ri] = arr[i];
            else ans[++le] = arr[i];
        }
    }
    else {
        int tmp;
        for (i = 1; i <= n; i++) {
            if (!v[i]) {
                tmp = i;
                break;
            }
        }
        ans[1] = 1;
        ans[n] = tmp;
        int le = 1, ri = n;
        for (i = 1; i < n; i++) {
            if (ans[le] < ans[ri]) ans[--ri] = arr[i];
            else ans[++le] = arr[i];
        }
    }
    for (i = 1; i <= n; i++) cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int T; cin >> T;
    while (T--) solve();
}
