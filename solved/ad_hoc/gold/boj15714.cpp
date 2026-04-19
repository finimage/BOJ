#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, aa[1000001], bb[1000001];
ll arr[1000001];

void solve() {
    int i; cin >> n;
    for (i = 1; i <= n; i++) cin >> aa[i];
    for (i = 1; i <= n; i++) cin >> bb[i];
    for (i = 1; i <= n; i++) arr[i] = (ll)aa[i] - bb[i];
    ll ans = 0;
    for (i = 1; i <= n; i++) {
        if (arr[i] > 0) {
            if (arr[i - 1] <= 0) ans += arr[i];
            else ans += max(0LL, arr[i] - arr[i - 1]);
        }
    }
    for (i = 1; i <= n; i++) arr[i] = -arr[i];
    for (i = 1; i <= n; i++) {
        if (arr[i] > 0) {
            if (arr[i - 1] <= 0) ans += arr[i];
            else ans += max(0LL, arr[i] - arr[i - 1]);
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
