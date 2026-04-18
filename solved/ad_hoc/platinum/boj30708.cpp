#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

int n, arr[100001];
unordered_map<int, int> um;
vector<int> path, ans, ans2;

void find_path(int node) {
	um[node]--;
	int tf = 0;
	path.push_back(node);
	if (um.count(node - 1)) {
		if (um[node - 1] > 0) {
			find_path(node - 1);
			tf = 1;
		}
	}
	if (tf) return;
	if (um.count(node + 1)) {
		if (um[node + 1] > 0) {
			find_path(node + 1);
		}
	}
}

void update_path(int node) {
	int tf = 0;
	if (um.count(node - 1)) {
		if (um[node - 1] > 0) {
			um[node - 1]--;
			ans.push_back(node - 1);
			update_path(node - 1);
			tf = 1;
		}
	}
	if (tf) return;
	if (um.count(node + 1)) {
		if (um[node + 1] > 0) {
			um[node + 1]--;
			ans.push_back(node + 1);
			update_path(node + 1);
		}
	}
}

void update_path2(int node) {
	int tf = 0;
	if (um.count(node - 1)) {
		if (um[node - 1] > 0) {
			um[node - 1]--;
			ans2.push_back(node - 1);
			update_path(node - 1);
			tf = 1;
		}
	}
	if (tf) return;
	if (um.count(node + 1)) {
		if (um[node + 1] > 0) {
			um[node + 1]--;
			ans2.push_back(node + 1);
			update_path(node + 1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, start; cin >> n;
	if (n == 1) {
		cin >> n;
		cout << n;
		return 0;
	}
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		start = arr[i];
		if (um.count(arr[i])) um[arr[i]]++;
		else um[arr[i]] = 1;
	}
	find_path(start);
	for (auto& iter : path) {
		ans.push_back(iter);
		int k = 0;
		if (um.count(iter - 1)) k += um[iter - 1];
		if (um.count(iter + 1)) k += um[iter + 1];
		while (um[iter] > 0 && k > 0) update_path(iter);
	}
	update_path2(ans[0]);
	if (ans.size() + ans2.size() != n) cout << -1;
	else {
		while (!ans2.empty()) {
			cout << ans2.back() << ' ';
			ans2.pop_back();
		}
		for (auto& iter : ans) cout << iter << ' ';
	}
}
