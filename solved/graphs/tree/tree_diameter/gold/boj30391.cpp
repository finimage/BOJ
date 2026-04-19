#include<iostream>
#include<queue>
#include<vector>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

vector<pii> ans;
queue<int> q;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, i, j, a; cin >> n >> k;
	q.push(1);
	q.push(2);
	ans.push_back({ 1,2 });
	for (i = 3; i <= n; i++) {
		a = q.front();
		q.pop();
		for (j = 0; j < k - 1; j++) {
			q.push(i + j);
			ans.push_back({ a,i + j });
			if (i + j >= n) break;
		}
		i += k - 2;
	}
	for (auto& iter : ans) cout << iter.x << ' ' << iter.y << '\n';
}
