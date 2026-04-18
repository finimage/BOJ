#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n, m;
ll arr[1000001];
int dp[1000001][2];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i; cin >> n >> m;
    for (i = 1; i <= n; i++) cin >> arr[i];
    dp[1][1] = 1;
    for (i = 2; i <= n; i++) {
        if (abs(arr[i] - arr[i - 1]) < m) {
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
        }
        else {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + 1;
        }
    }
    cout << min(dp[n][0], dp[n][1]);
}
