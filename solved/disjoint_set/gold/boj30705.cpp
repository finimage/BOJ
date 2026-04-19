#include<bits/stdc++.h>
using namespace std;

int n, m, parent[500001];

int find_(int a) {
    if (a == parent[a]) return a;
    return parent[a] = find_(parent[a]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b, ans = 0, cnt = 0, k; cin >> n >> m;
    for (i = 1; i <= n; i++) parent[i] = i;
    for (i = 0; i < m; i++) {
        cin >> a >> b;
        cnt++;
        k = 0;
        while (1) {
            a = find_(a);
            if (a < b) {
                k++;
                parent[a] = a + 1;
                a++;
            }
            if (a >= b) break;
        }
        if (k > cnt) {
            ans += k - cnt;
            cnt = 0;
        }
        else cnt -= k;
    }
    cout << ans;
}
