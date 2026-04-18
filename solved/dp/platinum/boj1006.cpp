#include<iostream>
using namespace std;

int N, W, arr[2][10002], dp[3][10002];

void res(int index) {
    for (int i = index; i <= N; i++) {
        dp[0][i + 1] = min(dp[1][i], dp[2][i]) + 1;
        if (arr[0][i] + arr[1][i] <= W) dp[0][i + 1] = min(dp[0][i + 1], dp[0][i] + 1);
        if (i > 1 && arr[0][i] + arr[0][i - 1] <= W && arr[1][i] + arr[1][i - 1] <= W) dp[0][i + 1] = min(dp[0][i + 1], dp[0][i - 1] + 2);
        if (i < N) {
            dp[1][i + 1] = min(dp[0][i + 1] + 1, ((arr[0][i] + arr[0][i + 1] <= W) ? min(dp[0][i + 1] + 1, dp[2][i] + 1) : 20001));
            dp[2][i + 1] = min(dp[0][i + 1] + 1, ((arr[1][i] + arr[1][i + 1] <= W) ? min(dp[0][i + 1] + 1, dp[1][i] + 1) : 20001));
        }
    }
}

void solve() {
    int i, j, ans = 20001; cin >> N >> W;
    for (i = 0; i < 2; i++) {
        for (j = 1; j <= N; j++) cin >> arr[i][j];
    }
    dp[0][1] = 0;
    dp[1][1] = 1;
    dp[2][1] = 1;
    res(1);
    ans = min(ans, dp[0][N + 1]);
    if (N > 1) {
        if (arr[0][1] + arr[0][N] <= W) {
            dp[0][2] = 1;
            dp[1][2] = 2;
            dp[2][2] = (arr[1][1] + arr[1][2] <= W) ? 1 : 2;
            res(2);
            ans = min(ans, dp[2][N] + 1);
        }
        if (arr[1][1] + arr[1][N] <= W) {
            dp[0][2] = 1;
            dp[1][2] = (arr[0][1] + arr[0][2] <= W) ? 1 : 2;
            dp[2][2] = 2;
            res(2);
            ans = min(ans, dp[1][N] + 1);

        }
        if (arr[0][1] + arr[0][N] <= W && arr[1][1] + arr[1][N] <= W) {
            dp[0][2] = 0;
            dp[1][2] = 1;
            dp[2][2] = 1;
            res(2);
            ans = min(ans, dp[0][N] + 2);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
