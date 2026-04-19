#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
using namespace std;

int n, arr[200001];
ll dp[200001];

void solve() {
    int i; cin >> n;
    for (i = 1; i <= n; i++) arr[i] = i;
    for (i = n; i >= 2; i -= 4) swap(arr[i], arr[i - 1]);
    dp[1] = arr[1];
    for (i = 2; i <= n; i++) dp[i] = max(dp[i - 1], dp[i - 2] + arr[i]);
    //cout << dp[n] << ' ' << (n * (n + 1) / 2 + 1) / 2;
    for (i = 1; i <= n; i++) cout << arr[i] << ' ';
    cout << '\n' << dp[n];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
