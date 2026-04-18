#include<bits/stdc++.h>
using namespace std;

int w, h, n, d, arr[101], p[102];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, ans = 0, tmp; cin >> w >> h >> n >> d;
    for (i = 1; i <= n; i++) cin >> arr[i];
    for (i = 1; i <= n; i++) cin >> p[i];
    p[n + 1] = p[n];
    for (i = 1; i <= n; i++) {
        if (arr[i] < d) ans += p[i] * (arr[i] - arr[i - 1]);
        else {
            j = i;
            tmp = ans + p[i] * (arr[i] * 2 - d - arr[i - 1]);
            ans += p[i] * (d - arr[i - 1]);
            break;
        }
    }
    ans += p[j] * w;
    ans = min(ans, tmp + p[j + 1] * w);
    for (i = j + 1; i <= n; i++) {
        tmp += p[i] * 2 * (arr[i] - arr[i - 1]);
        ans = min(ans, tmp + p[i + 1] * w);
    }
    cout << ans;
}
