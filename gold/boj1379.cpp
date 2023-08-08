#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

struct info {
	int num, start, end;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.end > b.end;
	}
};

bool comp(const info& a, const info& b) {
	return a.start < b.start;
}

info arr[100001];
int ans[100001];
priority_queue<info, vector<info>, cmp> pq;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, cnt = 1; cin >> n;
	for (i = 0; i < n; i++) cin >> arr[i].num >> arr[i].start >> arr[i].end;
	sort(arr, arr + n, comp);
	pq.push(arr[0]);
	ans[arr[0].num] = cnt;
	for (i = 1; i < n; i++) {
		if (pq.top().end > arr[i].start) {
			pq.push(arr[i]);
			cnt++;
			ans[arr[i].num] = cnt;
		}
		else {
			ans[arr[i].num] = ans[pq.top().num];
			pq.pop();
			pq.push(arr[i]);
		}
	}
	cout << cnt << '\n';
	for (i = 1; i <= n; i++) cout << ans[i] << '\n';
}
