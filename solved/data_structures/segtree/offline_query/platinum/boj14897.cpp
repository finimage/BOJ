#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct query {
	int ind, x, y;
};

bool cmp(query a, query b) {
	return a.y < b.y;
}

int arr[1000001], tree[4000004];
unordered_map<int, int> check;
vector<query> q;
vector<int> ans;

void update(int start, int end, int ind, int i) {
	if (i < start || end < i) return;
	tree[ind]++;
	if (start == end) return;
	int mid = (start + end) / 2;
	update(start, mid, ind * 2, i);
	update(mid + 1, end, ind * 2 + 1, i);
}

int sum(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind];
	int mid = (start + end) / 2;
	return sum(start, mid, ind * 2, le, ri) + sum(mid + 1, end, ind * 2 + 1, le, ri);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, i, ind = 1; cin >> n;
	for (i = 1; i <= n; i++) cin >> arr[i];
	cin >> m;
	q = vector<query>(m);
	ans = vector<int>(m);
	for (i = 0; i < m; i++) {
		cin >> q[i].x >> q[i].y;
		q[i].ind = i;
	}
	sort(q.begin(), q.end(), cmp);
	for (i = 0; i < m; i++) {
		while (ind <= q[i].y) {
			if (check.count(arr[ind])) update(1, n, 1, check[arr[ind]]);
			check[arr[ind]] = ind;
			ind++;
		}
		ans[q[i].ind] = q[i].y - q[i].x + 1 - sum(1, n, 1, q[i].x, q[i].y);
	}
	for (auto& iter : ans) cout << iter << '\n';
}
