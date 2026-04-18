#include<iostream>
#define ll long long
using namespace std;

ll arr[200001];
int total;

void solve() {
	int n, i, neg = 0, pos = 0; cin >> n;
    n += total;
	cin >> arr[total];
	for (i = total + 1; i < n - 1; i++) {
		cin >> arr[i];
		if (arr[i - 1] > 0) {
			if (arr[i] > 0) pos++;
			else {
				if (arr[i] + arr[i - 1] > 0) arr[i] += arr[i - 1];
				else pos++;
			}
		}
		else if (arr[i - 1] < 0) {
			if (arr[i] > 0) {
				if (arr[i] + arr[i - 1] > 0) arr[i] += arr[i - 1];
				else neg++;
			}
			else arr[i] += arr[i - 1];
		}
	}
	if (n > 1 + total) {
		cin >> arr[n - 1];
		if (arr[n - 2] > 0) {
			if (arr[n - 1] > 0) pos += 2;
			else if (arr[n - 1] + arr[n - 2] > 0) pos++;
		}
		else if (arr[n - 2] < 0) {
			if (arr[n - 1] > 0) {
				if (arr[n - 1] + arr[n - 2] > 0) pos++;
			}
			else neg++;
		}
	}
	if (n == 1 + total && arr[total] > 0) pos++;
    total = n;
	cout << (pos > neg ? "YES\n" : "NO\n");
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
