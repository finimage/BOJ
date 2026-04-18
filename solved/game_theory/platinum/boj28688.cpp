#include<iostream>
#define ll long long
using namespace std;

void solve() {
	ll n, m; cin >> n >> m;
	if (n == 1 || n == 2 || m == 1 || m == 2) cout << "First\n";
	else {
		if (n % 2 == 1 && m % 2 == 1) cout << "First\n";
		else cout << "Second\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
