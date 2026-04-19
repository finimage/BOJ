#include<bits/stdc++.h>
#define ld long double
using namespace std;

ld dp[1000002][2], prefix_sum[1000002][2];
string s;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, l; cin >> s;
    l = s.size();
    s = '!' + s;
    for (i = l; i > 0; i--) {
        prefix_sum[i][0] = prefix_sum[i + 1][0] + (s[i] == 'W') * (l - i + 1);
        prefix_sum[i][1] = prefix_sum[i + 1][1] + (s[i] == 'C') * (l - i + 1);
        //cout << prefix_sum[i][0] << ' ' << prefix_sum[i][1] << '\n';
    }
    for (i = l; i > 0; i--) {
        dp[i][0] = (prefix_sum[i][s[i] == 'W'] + dp[i + 1][1]) / (l - i + 1);
        dp[i][1] = dp[i][0] + dp[i + 1][1];
        //cout << dp[i][0] << ' ' << dp[i][1] << '\n';
    }
    cout << fixed << setprecision(15);
    cout << dp[1][0];
}
