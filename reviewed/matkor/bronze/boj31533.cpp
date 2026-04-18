#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    long double a, m, n, ans = 200; cin >> a >> m >> n;
    ans = min(ans, 2 * m / a);
    ans = min(ans, max(m / a, n));
    ans = min(ans, max(m, n / a));
    ans = min(ans, 2 * n / a);
    printf("%.10Lf", ans);
}
