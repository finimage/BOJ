#include<bits/stdc++.h>
#define ld long double
using namespace std;

int n;
ld dp[100001], p[11], q[11];
string s;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b;
    p[0] = 1;
    for (i = 1; i <= 10; i++) {
        cin >> a >> b;
        p[i] = (ld)a / (ld)(a + b);
        q[i] = (ld)b / (ld)(a + b);
    }
    cin >> n >> s;
    s = '!' + s;
    for (i = 1; i <= n; i++) {
        if (s[i - 1] == s[i]) dp[i] = dp[i - 1] * p[s[i] - '0'] + dp[i - 2] * q[s[i] - '0'] + 1;
        else {
            dp[i] = dp[i - 1] + p[s[i] - '0'];
            if (p[10] == 0) dp[i] += 3 * q[s[i] - '0'];
            else if (q[10] == 0) dp[i] += 2 * q[s[i] - '0'];
            else dp[i] += (1 + min(p[10] + q[10] * (2 + q[s[i] - '0'] * p[10]) / (1 - q[10] * q[s[i] - '0']), 2 * q[10] + 2 * (1 + q[10]) * p[10] / q[10])) * q[s[i] - '0'];
        }
    }
    cout << setprecision(10) << dp[n];
}
