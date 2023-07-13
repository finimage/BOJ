#include<iostream>
#include<unordered_map>
#define INF 50000
using namespace std;

int n, arr[1001][2];
bool check[1001];

int solve(int ind) {
    unordered_map<float, int> um;
    int i, ans = 0;
    check[ind] = true;
    for (i = 0; i < n; i++) {
        if (check[i]) continue;
        if (arr[ind][0] == arr[i][0]) {
            if (um.count(INF)) um[INF]++;
            else um.insert({ INF,1 });
            ans = max(ans, um[INF]);
        }
        else {
            float k = (float)(arr[ind][1] - arr[i][1]) / (arr[ind][0] - arr[i][0]);
            if (um.count(k)) um[k]++;
            else um.insert({ k,1 });
            ans = max(ans, um[k]);
        }
    }
    return ans + 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, ans = 0;
    cin >> n;
    for (i = 0; i < n; i++) cin >> arr[i][0] >> arr[i][1];
    for (i = 0; i < n - 2; i++) ans = max(ans, solve(i));
    if (ans > 2) cout << ans;
    else cout << -1;
}
