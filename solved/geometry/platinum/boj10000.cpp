#include<iostream>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct info {
	int O, R;
};

bool cmp(const info& a, const info& b) {
	if (a.O - a.R < b.O - b.R) return 1;
	else if (a.O - a.R == b.O - b.R && a.R > b.R) return 1;
	return 0;
}

info arr[300001];
unordered_map<int, int> parent;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, ans = 1; cin >> n;
	for (i = 1; i <= n; i++) cin >> arr[i].O >> arr[i].R;
	sort(arr + 1, arr + n + 1, cmp);
	for (i = 1; i <= n; i++) {
		ans++;
		if (!parent.count(arr[i].O - arr[i].R) && !parent.count(arr[i].O + arr[i].R)) {
			parent[arr[i].O - arr[i].R] = i;
			parent[arr[i].O + arr[i].R] = i;
		}
		else if (!parent.count(arr[i].O - arr[i].R) && parent.count(arr[i].O + arr[i].R)) {
			parent[arr[i].O - arr[i].R] = parent[arr[i].O + arr[i].R];
		}
		else if (parent.count(arr[i].O - arr[i].R) && !parent.count(arr[i].O + arr[i].R)) {
			parent[arr[i].O + arr[i].R] = parent[arr[i].O - arr[i].R];
		}
		else if (parent[arr[i].O - arr[i].R] == parent[arr[i].O + arr[i].R]) {
			ans++;
		}
		else if (parent[arr[i].O - arr[i].R] != parent[arr[i].O + arr[i].R]) {
			parent[arr[i].O - arr[i].R] = parent[arr[i].O + arr[i].R];
		}
	}
	cout << ans;
}
