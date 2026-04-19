#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n; ll sum;
vector<int> arr;

void solve() {
    int i, ans = 0; cin >> n;
    arr.resize(n);
    for (i = 0; i < n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());
    for (i = 0; i < n; i++) {
        sum += arr[i];
        if (arr[i] == ans) ans++;
    }
    cout << (sum == 0 ? 0 : ans + 1) << '\n';
    for (auto& iter : arr) cout << iter << ' ';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
