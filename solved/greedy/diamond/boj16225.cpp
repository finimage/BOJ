#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

/*
par[i - 1] = i이면 i는 a를 얻기 위해서든 다른 a를 얻기 위해 희생된 것이든 사용되었다는 것
만약 i를 쓸려고 봤는데 사용된거면 희생시킬 것 2개가 필요
사용 안 된거면 이를 위해 희생할 것 1개만 있으면 됨
희생시키는 것들은 순서 상 b가 더 큰 것들임(정렬해놓고 y로 인덱스를 씀)
만약 이걸 사용 못해도 이미 더 이득인 것을 사용(x로 정렬)해서 못하는 것이기에 이득
*/

int n, par[200002];
ll ans;
pii arr[200001];

int find_(int a) {
    if (a == par[a]) return a;
    return par[a] = find_(par[a]);
}

bool cmp(pii a, pii b) {
	return a.y < b.y;
}

void solve() {
	int i; cin >> n;
	for (i = 1; i <= n; i++) cin >> arr[i].x;
	for (i = 1; i <= n; i++) cin >> arr[i].y;
	for (i = 1; i <= n + 1; i++) par[i] = i;
	sort(arr + 1, arr + n + 1, cmp);
	for (i = 1; i <= n; i++) arr[i].y = i;
	sort(arr + 1, arr + n + 1);
	for (i = n; i > 0; i--) {
	    int k = find_(arr[i].y - 1);
	    if (arr[i].y - 1 != k) {
	        if (k < n + 1) {
	            int kk = find_(k + 1) + 1;
	            if (kk < n + 1) {
	                ans += arr[i].x;
	                par[k] = k + 1;
	                par[kk - 1] = kk;
	            }
	        }
	        continue;
	    }
	    k = find_(arr[i].y) + 1;
	    if (k < n + 1) {
	        ans += arr[i].x;
	        par[k - 1] = k;
	        par[arr[i].y - 1] = arr[i].y;
	    }
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T = 1; // cin >> T;
	while (T--) solve();
}
