#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> arr[2];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, j, le[2], ri[2], ans = 0; cin >> n;
	le[0] = le[1] = 0;
	ri[0] = ri[1] = n - 1;
	arr[0] = vector<int>(n);
	arr[1] = vector<int>(n);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < n; j++) cin >> arr[i][j];
	}
	sort(arr[0].begin(), arr[0].end());
	sort(arr[1].begin(), arr[1].end());
	while (le[0] <= ri[0]) {
		if (arr[0][ri[0]] > arr[1][ri[1]]) {
			ans += 100;
			ri[0]--;
			ri[1]--;
		}
		else if (arr[0][le[0]] > arr[1][le[1]]) {
			ans += 100;
			le[0]++;
			le[1]++;
		}
		else {
			if (arr[0][le[0]] == arr[1][ri[1]]) ans += 20;
			else ans -= 50;
			le[0]++;
			ri[1]--;
		}
	}
	cout << ans;
}
