#include<iostream>
#include<unordered_map>
#define ll long long
using namespace std;

ll arr[200001];
unordered_map<ll, ll> um;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll n, k, ans = 0; cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		arr[i] += arr[i - 1];
		if (um.count(arr[i] - k * i)) ans += um[arr[i] - k * i];
		else um[arr[i] - k * i] = 0;
		um[arr[i] - k * i]++;
		if (arr[i] == k * i) ans++;
	}
	cout << ans;
}
