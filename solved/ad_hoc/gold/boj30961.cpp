#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;

int n, arr[1000001];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i;
	ll ans = 0; cin >> n;
	for (i = 0; i < n; i++) cin >> arr[i];
	sort(arr, arr + n);
	for (i = 1; i < n; i++) {
		ans ^= (ll)arr[i] * (ll)arr[i - 1];
		ans ^= (ll)arr[i] * (ll)arr[i];
	}
	cout << (ans ^ ((ll)arr[0] * (ll)arr[0]));
}
