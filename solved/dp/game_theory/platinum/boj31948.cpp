#include<bits/stdc++.h>
using namespace std;

int dp[1501][1501][3], w;
string s;

int top_down(int le, int ri, int k) {
    if (ri < le) return 0;
    if (dp[le][ri][k] != -1) return dp[le][ri][k];
    if (le == ri && k) return dp[le][ri][k] = 1;
    int res = 1;
    if (k == 0) {
        s[w] = '0';
        res &= top_down(le, ri, 1);
        s[w] = '1';
        res &= top_down(le, ri, 2);
        s[w] = '?';
    }
    if (s[le] != '?') {
        for (int i = le; i <= ri; i++) {
            if (s[le] == s[i]) res &= top_down(i + 1, ri, k);
            else break;
        }
    }
    if (s[ri] != '?') {
        for (int i = ri; i >= le; i--) {
            if (s[ri] == s[i]) res &= top_down(le, i - 1, k);
            else break;
        }
    }
    return dp[le][ri][k] = (res ? 0 : 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;
    int tf = 1, l = s.size(), i, j;
    for (i = 0; i < l; i++) {
        if (s[i] == '?') {
            tf = 0;
            w = i;
            break;
        }
    }
    for (i = 0; i <= l; i++) {
        for (j = 0; j <= l; j++) dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = -1;
    }
    cout << top_down(0, (int)s.size() - 1, tf);
}
