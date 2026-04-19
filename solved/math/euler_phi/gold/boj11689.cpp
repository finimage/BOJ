#include<iostream>
#define ll long long
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll n, i, ans; cin >> n;
	ans = n;
	for (i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans /= i;
			ans *= i - 1;
			while (n % i == 0) n /= i;
		}
	}
	if (n != 1) {
		ans /= n;
		ans *= n - 1;
	}
	cout << ans;
}
