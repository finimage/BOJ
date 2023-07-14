#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

vector<int> v[2][51];
queue<int> q;
int arr[51];

int check(int a) {
	if (v[1][a].size() == 0) return 0;
	int ans = 0, i = 1;
	sort(v[1][a].begin(), v[1][a].end(), greater<>());
	for (auto iter = v[1][a].begin(); iter != v[1][a].end(); iter++) ans = max(ans, *iter + i++);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, i, temp, l, t;
	cin >> n >> temp;
	for (i = 1; i < n; i++) {
		cin >> temp;
		arr[temp]++;
		v[0][i].push_back(temp);
	}
	for (i = 0; i <= n; i++) {
		if (arr[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		temp = q.front();
		l = v[0][temp].size();
		t = check(temp);
		q.pop();
		for (i = 0; i < l; i++) {
			arr[v[0][temp][i]]--;
			v[1][v[0][temp][i]].push_back(t);
			if (arr[v[0][temp][i]] == 0) q.push(v[0][temp][i]);
		}
	}
	cout << t;
}
