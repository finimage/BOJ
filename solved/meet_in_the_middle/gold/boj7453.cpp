#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> arr[4], v[2];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j; cin >> n;
    for (i = 0; i < 4; i++) arr[i].resize(n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < 4; j++) cin >> arr[j][i];
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++){
            int k = arr[0][i] + arr[1][j];
            v[0].emplace_back(k);
            k = arr[2][i] + arr[3][j];
            v[1].emplace_back(-k);
        }
    }
    sort(v[1].begin(), v[1].end());
    long long ans = 0;
    for (auto& iter : v[0]) {
        int ri = upper_bound(v[1].begin(), v[1].end(), iter) - v[1].begin();
        int le = lower_bound(v[1].begin(), v[1].end(), iter) - v[1].begin();
        if (ri > le) ans += ri - le;
    }
    cout << ans;
}
