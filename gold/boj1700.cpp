#include<iostream>
using namespace std;

int arr[101];
bool check[101], new_check[101];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, i, j, cnt = 0, ans = 0; cin >> n >> k;
	for (i = 0; i < k; i++) cin >> arr[i];
	for (i = 0; i < k; i++) {
		if (check[arr[i]]) continue;
		else if (cnt < n) {
			check[arr[i]] = 1;
			cnt++;
		}
		else {
			int new_cnt = 0;
			for (j = i; j < k; j++) {
				if (check[arr[j]] && !new_check[arr[j]]) {
					new_cnt++;
					if (new_cnt == n) break;
					new_check[arr[j]] = 1;
				}
			}
			for (j = 1; j <= 100; j++) {
				if (check[j] && !new_check[j]) {
					check[j] = 0;
					ans++;
					break;
				}
			}
			for (j = 1; j <= 100; j++) new_check[j] = 0;
			check[arr[i]] = 1;
		}
	}
	cout << ans;
}
