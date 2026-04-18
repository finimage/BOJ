#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;
 
ll n, q, f, ans;
ll arr[1000001];
priority_queue<pll> pq;
 
void solve() {
    ll i, Max = 0; cin >> n >> q >> f;
    for (i = 0; i < n; i++) {
        cin >> arr[i];
        Max = max(Max, arr[i]);
    }
    for (i = 0; i < min(f, n); i++) pq.push({arr[i] - i, i});
    for (i = 0; i < q; i++) {
        while (!pq.empty() && pq.top().y < i) pq.pop();
        ans += max(Max, pq.top().x + i + f - 1);
        pq.push({arr[(i + min(f, n)) % n] - i - min(f, n), i + min(f, n)});
    }
    cout << ans;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
