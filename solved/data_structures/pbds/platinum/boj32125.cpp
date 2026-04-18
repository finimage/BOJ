#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ll, null_type, less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>


ll n, k;
int arr[500001];

void solve() {
    map<ll, ordered_set> ms;
    int i; cin >> n >> k;
    for (i = 1; i <= n; i++) cin >> arr[i];
    ll dif = 0, vv = 0, a, ans = 0;
    for (i = 1; i <= n; i++) {
        cin >> a;
        if (arr[i] == 1) {
            vv++;
            dif += a;
            if (ms.count(vv)) {
                ll ri = ms[vv].order_of_key(k + dif + 1);
                ll le = ms[vv].order_of_key(dif - k);
                ans += ri - le;
                ms[vv].insert(dif);
            }
            else {
                ms[vv] = ordered_set();
                ms[vv].insert(dif);
            }
            if (vv == 0 && -k <= dif && dif <= k) ans++;
        }
        else {
            vv--;
            dif -= a;
            if (ms.count(vv)) {
                ll ri = ms[vv].order_of_key(k + dif + 1);
                ll le = ms[vv].order_of_key(dif - k);
                ans += ri - le;
                ms[vv].insert(dif);
            }
            else {
                ms[vv] = ordered_set();
                ms[vv].insert(dif);
            }
            if (vv == 0 && -k <= dif && dif <= k) ans++;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; cin >> T;
    while (T--) solve();
}
